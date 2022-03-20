#include "Screen_SSD1306.h"

void Screen_SSD1306::init()
{
  dev.init();
  send_init_commands();
  display_on();
}

void Screen_SSD1306::send_init_commands()
{
  if (height == 32)
  {
    write_cmd(0xA8, 0x1F);
    write_cmd(0xDA, 0x02);
  }

  /* vertical shift, 0 ~ 63 */
  // write_cmd(0xD3, 20);

  /* Ratio/Oscillator & Clock Divide */
  // write_cmd(0xD5, 0xF0);

  // write_cmd(0xD9, 0x22);

}

void Screen_SSD1306::set_brightness(uint8_t value)
{
  write_cmd(0x81, value);
}

void Screen_SSD1306::up_down_invert()
{
  write_cmd(0xA1);
}

void Screen_SSD1306::color_reverse()
{
  write_cmd(0xA7);
}

void Screen_SSD1306::write_data(uint8_t data)
{
  dev.start_transmit();
  dev.write_byte(0x40);
  dev.write_byte(data);
  dev.stop_transmit();
}

void Screen_SSD1306::write_cmd(uint8_t cmd)
{
  dev.start_transmit();
  dev.write_byte(0x00);
  dev.write_byte(cmd);
  dev.stop_transmit();
}

void Screen_SSD1306::write_cmd(uint8_t cmd, uint8_t param)
{
  dev.start_transmit();
  dev.write_byte(0x00);
  dev.write_byte(cmd);
  dev.write_byte(param);
  dev.stop_transmit();
}

void Screen_SSD1306::display_on()
{
  // turn on the charge pump
  write_cmd(0x8D, 0x14);
  // turn on display
  write_cmd(0xAF);
}

void Screen_SSD1306::display_off()
{
  // turn off the charge pump
  write_cmd(0x8D, 0x10);
  // turn off display
  write_cmd(0xAE);
}

void Screen_SSD1306::flush()
{
  dev.start_transmit();
  // to implement
  dev.stop_transmit();
}

void Screen_SSD1306::draw_point(int x, int y, Color_1bit color)
{
  if (x >= width || y >= height)
  {
    return;
  }
  int page_idx = y / 8;
  int byte_idx = y % 8;

  int tmp = buf[x][page_idx];
  tmp &= ~(1 << byte_idx);
  tmp |= color << byte_idx;
  buf[x][page_idx] = tmp;

  /*
  dev.start_transmit();
  dev.write_byte(0x00);
  dev.write_byte(0xB0 + page_idx);
  dev.write_byte(((x >> 4) & 0x0F) | 0x10);
  dev.write_byte(x & 0x0F);
  dev.write_byte(0x40);
  dev.write_byte(tmp);
  dev.stop_transmit();
  */

  write_cmd(0xB0 + page_idx);
  write_cmd(((x >> 4) & 0x0F) | 0x10);
  write_cmd(x & 0x0F);
  write_data(tmp);
}
