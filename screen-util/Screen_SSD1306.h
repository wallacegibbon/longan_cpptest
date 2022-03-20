#ifndef __SSD1306_H
#define __SSD1306_H

/**
 * SSD1306 is a 128 x 64 Dot Matrix OLED/PLED Segment/Common Driver with Controller
 */

#include <stdint.h>
#include "Screen.h"
#include "Screen_Color.h"
#include "Common_IIC.h"

class Screen_SSD1306 : public Screen<Color_1bit>
{
public:
  Screen_SSD1306(int _dev, int addr, int width, int height)
      : dev(_dev, addr), Screen(width, height) {}

  void init();
  void display_on();
  void display_off();

  void set_brightness(uint8_t value);
  void up_down_invert();
  void color_reverse();

  void draw_point(int x, int y, Color_1bit color) override;

private:
  void send_init_commands();
  void write_data(uint8_t data);
  void write_cmd(uint8_t cmd);
  void write_cmd(uint8_t cmd, uint8_t param);
  void flush();

  uint8_t buf[128][8];
  IIC_Dev dev;
};

#endif
