#include "Screen_SSD1306.h"

void Screen_SSD1306::init()
{
  dev.init();

  write_cmd(0x40);
  write_cmd(0xb0);

  write_cmd(0xc8);

  write_cmd(0x81);
  write_cmd(0xff);

  write_cmd(0xa1);

  write_cmd(0xa6);

  write_cmd(0xa8);
  write_cmd(0x1f);

  write_cmd(0xd3);
  write_cmd(0x00);

  write_cmd(0xd5);
  write_cmd(0xf0);

  write_cmd(0xd9);
  write_cmd(0x22);

  write_cmd(0xda);
  write_cmd(0x02);

  write_cmd(0xdb);
  write_cmd(0x49);

  display_on();
}

void Screen_SSD1306::write_data(uint8_t data)
{
  dev.start_transmit();
  dev.write_byte(0x40);
  dev.write_byte(data);
  dev.stop_transmit();
}

void Screen_SSD1306::write_cmd(uint8_t data)
{
  dev.start_transmit();
  dev.write_byte(0x00);
  dev.write_byte(data);
  dev.stop_transmit();
}

void Screen_SSD1306::display_on()
{
  write_cmd(0x8d);
  write_cmd(0x14);
  write_cmd(0xaf);
}

void Screen_SSD1306::display_off()
{
  write_cmd(0x8d);
  write_cmd(0x10);
  write_cmd(0xae);
}

void Screen_SSD1306::addr_set(int x1, int y1, int x2, int y2)
{
  write_cmd(0xb0 + y1);
  write_cmd((x1 & 0xf) >> 4 | 0x10);
  write_cmd(x1 & 0xf);
}

void Screen_SSD1306::draw_point(int x, int y, Color_1bit color)
{
  addr_set(x, y, x, y);
  write_data(color);
}

void Screen_SSD1306::fill(int x1, int y1, int x2, int y2, Color_1bit color)
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