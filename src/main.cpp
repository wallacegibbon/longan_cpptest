#include <stdio.h>
#include <stdint.h>
#include "nuclei_sdk_soc.h"
#include "RingBuffer.h"
#include "screen-util/Screen_ST7735.h"
#include "screen-util/Screen_SSD1306.h"
#include "screen-util/Common_IO.h"

Screen_ST7735 longan_screen(SPI0, GPIOB, GPIO_PIN_2, GPIOB, GPIO_PIN_1, GPIOB, GPIO_PIN_0, 160, 80);
Screen_SSD1306_IIC ext_screen_1(I2C0, 0x3C, 128, 64);
// Screen_SSD1306_IIC ext_screen_1(I2C0, 0x3C, 128, 32);

RingBuffer<uint8_t, 10> usart0_recv_buffer;

OutPin red_LED(GPIOC, GPIO_PIN_13);

class LED_Controller
{
public:
    LED_Controller(int init_port, int init_pin) : dev(init_port, init_pin) {}
    void init() { dev.init(); }
    void toggle();

private:
    OutPin dev;
    bool state = true;
};

void LED_Controller::toggle()
{
    state = !state;
    if (state)
    {
        dev.clr();
    }
    else
    {
        dev.set();
    }
}

LED_Controller green_LED(GPIOA, GPIO_PIN_1);
LED_Controller blue_LED(GPIOA, GPIO_PIN_2);

static void clock_init()
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_AF);

    rcu_periph_clock_enable(RCU_SPI0);
    // IO for SPI0: NSS/PA4, SCK/PA5, MOSI/PA7
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);

    rcu_periph_clock_enable(RCU_I2C0);
    gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7);

    rcu_periph_clock_enable(RCU_USART0);
    // IO for USART0
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
}

static void interrupt_init()
{
    ECLIC_Register_IRQ(USART0_IRQn, ECLIC_NON_VECTOR_INTERRUPT, ECLIC_LEVEL_TRIGGER, 1, 0, nullptr);
}

static void uart_init()
{
    usart_deinit(USART0);
    usart_baudrate_set(USART0, 128000);
    usart_word_length_set(USART0, USART_WL_8BIT);
    usart_stop_bit_set(USART0, USART_STB_1BIT);
    usart_parity_config(USART0, USART_PM_NONE);
    usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_enable(USART0);

    // enable the interrupt after initializing the usart
    usart_interrupt_enable(USART0, USART_INT_RBNE);
}

static void update_loop_display()
{
    static unsigned short current_color = 0;
    for (int i = 0; i < 30; i++)
    {
        current_color += 20;
        longan_screen.draw_circle(80, 40, i, static_cast<Color_16bit>(current_color));
        ext_screen_1.draw_circle(64, 32, i, static_cast<Color_1bit>(1));
    }
}

static void wfi_test_loop()
{
    while (1)
    {
        printf("entering sleep mode...\r\n");
        pmu_to_sleepmode(WFI_CMD);
        // pmu_to_deepsleepmode(PMU_LDO_NORMAL, WFI_CMD);
        // pmu_to_standbymode(WFI_CMD);
    }
}

static void circle_display_loop()
{
    while (1)
    {
        red_LED.set();
        update_loop_display();
        red_LED.clr();
        update_loop_display();
    }
}

static void init_system()
{
    clock_init();
    uart_init();
    interrupt_init();

    red_LED.init();
    green_LED.init();
    blue_LED.init();

    longan_screen.init();
    ext_screen_1.init();

    __enable_irq();
}

int main(int argc, const char **argv)
{
    init_system();
    printf("== %s ==\r\n", "the system is ready");

    longan_screen.clear(BLACK_16bit);
    longan_screen.draw_rectangle(80 - 50, 40 - 20, 80 + 50, 40 + 20, CYAN_16bit);
    longan_screen.draw_circle(80 - 50, 40 - 20, 5, YELLOW_16bit);

    // ext_screen_1.set_brightness(0x01);
    // ext_screen_1.color_reverse();
    // ext_screen_1.up_down_invert();
    ext_screen_1.clear(BLACK_1bit);
    ext_screen_1.draw_rectangle(64 - 50, 32 - 20, 64 + 50, 32 + 20, WHITE_1bit);
    ext_screen_1.draw_circle(64 - 50, 32 - 20, 5, WHITE_1bit);

    circle_display_loop();

    // wfi_test_loop();

    return 0;
}

#ifdef __cplusplus
extern "C"
{
#endif

    int _put_char(int ch)
    {
        usart_data_transmit(USART0, static_cast<uint8_t>(ch));
        while (usart_flag_get(USART0, USART_FLAG_TBE) == RESET)
            continue;
        return ch;
    }

    void USART0_IRQHandler()
    {
        uint8_t data = static_cast<uint8_t>(usart_data_receive(USART0));

        uint8_t tmp;
        if (usart0_recv_buffer.rest() == 0)
        {
            usart0_recv_buffer.get(&tmp, 1);
        }
        usart0_recv_buffer.put(&data, 1);

        switch (data)
        {
        case 'g':
            green_LED.toggle();
            break;
        case 'b':
            blue_LED.toggle();
            break;
        default:
            break;
        }
    }

#ifdef __cplusplus
}
#endif
