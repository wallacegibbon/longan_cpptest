#ifndef __SSD1306_H
#define __SSD1306_H

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
  void write_data(uint8_t data);
  void write_cmd(uint8_t data);
  void addr_set(int x1, int y1, int x2, int y2);

  void display_on();
  void display_off();

  void draw_point(int x, int y, Color_1bit color) override;
  void fill(int x1, int y1, int x2, int y2, Color_1bit color) override;

private:
  void send_init_commands();
  IIC_Dev dev;
};

#endif
