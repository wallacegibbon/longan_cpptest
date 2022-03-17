#include <nuclei_sdk_soc.h>
#include <stdio.h>
#include <stdint.h>
#include "Screen_ST7735.h"
#include "RingBuffer.h"

Screen_ST7735 longan_screen(SPI0, GPIOB, GPIO_PIN_1, GPIOB, GPIO_PIN_2, GPIOB, GPIO_PIN_0, 160, 80);

RingBuffer<uint8_t, 10> usart0_recv_buffer;

static void uart_init()
{
  rcu_periph_clock_enable(RCU_GPIOA);
  rcu_periph_clock_enable(RCU_USART0);

  ECLIC_Register_IRQ(USART0_IRQn, ECLIC_NON_VECTOR_INTERRUPT, ECLIC_LEVEL_TRIGGER, 1, 0, nullptr);

  // IO for USART0
  gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
  gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

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

static void led_init()
{
  rcu_periph_clock_enable(RCU_GPIOA);
  rcu_periph_clock_enable(RCU_GPIOC);

  // trun off all LEDs
  gpio_bit_set(GPIOA, GPIO_PIN_1 | GPIO_PIN_2);
  gpio_bit_set(GPIOC, GPIO_PIN_13);

  // IO for LED
  gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_13);
  gpio_init(GPIOC, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_13);
}

void update_loop_display()
{
  static unsigned short current_color = 0;
  for (int i = 0; i < 36; i++)
  {
    current_color += 10;
    longan_screen.draw_circle(80, 40, i, static_cast<Color16>(current_color));
  }
}

void wfi_test_loop()
{
  while (1)
  {
    printf("entering sleep mode...\r\n");
    pmu_to_sleepmode(WFI_CMD);
    // pmu_to_deepsleepmode(PMU_LDO_NORMAL, WFI_CMD);
    // pmu_to_standbymode(WFI_CMD);
  }
}

void circle_display_loop()
{
  while (1)
  {
    gpio_bit_set(GPIOC, GPIO_PIN_13);
    update_loop_display();
    gpio_bit_reset(GPIOC, GPIO_PIN_13);
    update_loop_display();
  }
}

int main(int argc, const char **argv)
{
  uart_init();
  led_init();

  __enable_irq();

  printf("== %s ==\r\n", "the system is ready");

  longan_screen.clear(BLACK);
  longan_screen.draw_rectangle(10, 10, 150, 70, CYAN);

  circle_display_loop();

  // wfi_test_loop();

  return 0;
}

class LED_Controller
{
public:
  LED_Controller(int init_port, int init_pin) : port(init_port), pin(init_pin), state(false) {}
  void toggle();

private:
  int port;
  int pin;
  bool state;
};

void LED_Controller::toggle()
{
  state = !state;
  if (state)
    gpio_bit_reset(port, pin);
  else
    gpio_bit_set(port, pin);
}

LED_Controller green_led(GPIOA, GPIO_PIN_1);
LED_Controller blue_led(GPIOA, GPIO_PIN_2);

#ifdef __cplusplus
extern "C"
{
#endif

  int _put_char(int ch)
  {
    usart_data_transmit(USART0, static_cast<uint8_t>(ch));
    while (usart_flag_get(USART0, USART_FLAG_TBE) == RESET)
      ;
    return ch;
  }

  void USART0_IRQHandler()
  {
    uint8_t data = static_cast<uint8_t>(usart_data_receive(USART0));

    uint8_t tmp;
    if (usart0_recv_buffer.rest() == 0)
      usart0_recv_buffer.get(&tmp, 1);

    usart0_recv_buffer.put(&data, 1);

    if (data == 'g')
      green_led.toggle();
    else if (data == 'b')
      blue_led.toggle();
  }

#ifdef __cplusplus
}
#endif
