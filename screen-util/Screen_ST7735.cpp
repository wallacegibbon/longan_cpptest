#include "Screen_ST7735.h"

void Screen_ST7735::init()
{
  Screen_16bitColor_SPI::init();

  rst.clr();
  delay_1ms(200);
  rst.set();
  delay_1ms(20);

  send_init_commands();
}

void Screen_ST7735::send_init_commands()
{
  // turn off sleep mode
  write_cmd(0x11);
  delay_1ms(100);

  // display inversion mode (0 is black, -1 is white)
  write_cmd(0x21);

  // Set the frame frequency of the full colors normal mode
  write_cmd(0xB1);
  // Frame rate=fosc/((RTNA x 2 + 40) x (LINE + FPA + BPA +2))
  // fosc = 850kHz
  write_data8(0x05); // RTNA
  write_data8(0x3A); // FPA
  write_data8(0x3A); // BPA

  // Set the frame frequency of the Idle mode
  write_cmd(0xB2);
  // Frame rate=fosc/((RTNB x 2 + 40) x (LINE + FPB + BPB +2))
  // fosc = 850kHz
  write_data8(0x05); // RTNB
  write_data8(0x3A); // FPB
  write_data8(0x3A); // BPB

  // Set the frame frequency of the Partial mode/ full colors
  write_cmd(0xB3);
  write_data8(0x05);
  write_data8(0x3A);
  write_data8(0x3A);
  write_data8(0x05);
  write_data8(0x3A);
  write_data8(0x3A);

  write_cmd(0xB4);
  write_data8(0x03);

  write_cmd(0xC0);
  write_data8(0x62);
  write_data8(0x02);
  write_data8(0x04);

  write_cmd(0xC1);
  write_data8(0xC0);

  write_cmd(0xC2);
  write_data8(0x0D);
  write_data8(0x00);

  write_cmd(0xC3);
  write_data8(0x8D);
  write_data8(0x6A);

  write_cmd(0xC4);
  write_data8(0x8D);
  write_data8(0xEE);

  write_cmd(0xC5);
  write_data8(0x0E); // VCOM

  write_cmd(0xE0);
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

  write_cmd(0xE1);
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

  // 16 bit color
  write_cmd(0x3A);
  write_data8(0x05);

  write_cmd(0x36);
  write_data8(0x78);

  write_cmd(0x29); // Display On
}

void Screen_ST7735::addr_set(int x1, int y1, int x2, int y2)
{
  // column address settings
  write_cmd(0x2A);
  write_data(x1 + 1);
  write_data(x2 + 1);

  // row address setting
  write_cmd(0x2B);
  write_data(y1 + 26);
  write_data(y2 + 26);

  // memory write
  write_cmd(0x2C);
}

void Screen_ST7735::draw_point(int x, int y, Color_16bit color)
{
  if (x > width || y > height)
  {
    return;
  }
  addr_set(x, y, x, y);
  write_data(color);
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
