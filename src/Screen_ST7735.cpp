#include <nuclei_sdk_soc.h>
#include "Screen_ST7735.h"

void spi0_init()
{
  spi_parameter_struct spi;
  spi.trans_mode = SPI_TRANSMODE_FULLDUPLEX;
  spi.device_mode = SPI_MASTER;
  spi.frame_size = SPI_FRAMESIZE_8BIT;
  spi.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
  spi.nss = SPI_NSS_SOFT;
  spi.prescale = SPI_PSC_8;
  spi.endian = SPI_ENDIAN_MSB;

  spi_init(SPI0, &spi);
  spi_crc_polynomial_set(SPI0, 7);
  spi_enable(SPI0);
}

void Screen_ST7735::init()
{
  rcu_periph_clock_enable(RCU_GPIOA);
  rcu_periph_clock_enable(RCU_GPIOB);
  rcu_periph_clock_enable(RCU_AF);
  rcu_periph_clock_enable(RCU_SPI0);

  spi_cs_set();

  /* SPI0 GPIO config: NSS/PA4, SCK/PA5, MOSI/PA7 */
  gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
  gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2);

  spi0_init();

  gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_1);
  gpio_bit_reset(GPIOB, GPIO_PIN_0 | GPIO_PIN_1);

  spi_rst_clr();
  delay_1ms(200);
  spi_rst_set();
  delay_1ms(20);

  // turn off sleep mode
  write_reg(0x11);
  delay_1ms(100);

  // display inversion mode
  write_reg(0x21);

  // Set the frame frequency of the full colors normal mode
  write_reg(0xB1);

  // Frame rate=fosc/((RTNA x 2 + 40) x (LINE + FPA + BPA +2))
  // fosc = 850kHz
  write_data8(0x05); // RTNA
  write_data8(0x3A); // FPA
  write_data8(0x3A); // BPA

  // Set the frame frequency of the Idle mode
  write_reg(0xB2);

  // Frame rate=fosc/((RTNB x 2 + 40) x (LINE + FPB + BPB +2))
  // fosc = 850kHz
  write_data8(0x05); // RTNB
  write_data8(0x3A); // FPB
  write_data8(0x3A); // BPB

  // Set the frame frequency of the Partial mode/ full colors
  write_reg(0xB3);

  write_data8(0x05);
  write_data8(0x3A);
  write_data8(0x3A);
  write_data8(0x05);
  write_data8(0x3A);
  write_data8(0x3A);

  write_reg(0xB4);
  write_data8(0x03);

  write_reg(0xC0);
  write_data8(0x62);
  write_data8(0x02);
  write_data8(0x04);

  write_reg(0xC1);
  write_data8(0xC0);

  write_reg(0xC2);
  write_data8(0x0D);
  write_data8(0x00);

  write_reg(0xC3);
  write_data8(0x8D);
  write_data8(0x6A);

  write_reg(0xC4);
  write_data8(0x8D);
  write_data8(0xEE);

  write_reg(0xC5);
  write_data8(0x0E); // VCOM

  write_reg(0xE0);
  write_data8(0x10);
  write_data8(0x0E);
  write_data8(0x02);
  write_data8(0x03);
  write_data8(0x0E);
  write_data8(0x07);
  write_data8(0x02);
  write_data8(0x07);
  write_data8(0x0A);
  write_data8(0x12);
  write_data8(0x27);
  write_data8(0x37);
  write_data8(0x00);
  write_data8(0x0D);
  write_data8(0x0E);
  write_data8(0x10);

  write_reg(0xE1);
  write_data8(0x10);
  write_data8(0x0E);
  write_data8(0x03);
  write_data8(0x03);
  write_data8(0x0F);
  write_data8(0x06);
  write_data8(0x02);
  write_data8(0x08);
  write_data8(0x0A);
  write_data8(0x13);
  write_data8(0x26);
  write_data8(0x36);
  write_data8(0x00);
  write_data8(0x0D);
  write_data8(0x0E);
  write_data8(0x10);

  // define the format of RGB picture data
  write_reg(0x3A);

  write_data8(0x05); // 16-bit/pixel

  write_reg(0x36);
  write_data8(0x78);

  write_reg(0x29); // Display On
}

void Screen_ST7735::addr_set(int x1, int y1, int x2, int y2)
{
  // column address settings
  write_reg(0x2a);
  write_data(x1 + 1);
  write_data(x2 + 1);

  // row address setting
  write_reg(0x2b);
  write_data(y1 + 26);
  write_data(y2 + 26);

  // memory write
  write_reg(0x2c);
}

void Screen_ST7735::fill(int x1, int y1, int x2, int y2, Color_16bit color)
{
  addr_set(x1, y1, x2, y2);
  for (int i = y1; i <= y2; i++)
  {
    for (int j = x1; j <= x2; j++)
    {
      write_data(color);
    }
  }
}

void Screen_ST7735::draw_point(int x, int y, Color_16bit color)
{
  addr_set(x, y, x, y);
  write_data(color);
}