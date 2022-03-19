#ifndef __SCREEN_ST7735_H
#define __SCREEN_ST7735_H

#include "Screen_16bitColor_SPI.h"

class Screen_ST7735 : public Screen_16bitColor_SPI
{
public:
  Screen_ST7735(int dev, int rst_port, int rst_pin, int cs_port, int cs_pin, int dc_port, int dc_pin, int width, int height)
      : Screen_16bitColor_SPI::Screen_16bitColor_SPI(dev, rst_port, rst_pin, cs_port, cs_pin, dc_port, dc_pin, width, height)
  {
    init();
  }

  void addr_set(int x1, int y1, int x2, int y2);

  void draw_point(int x, int y, Color_16bit color) override;
  void fill(int x1, int y1, int x2, int y2, Color_16bit color) override;

private:
  void init();
};

#endif
