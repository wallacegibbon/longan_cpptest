#ifndef __SCREEN_16BITCOLOR_SPI_H
#define __SCREEN_16BITCOLOR_SPI_H

#include <stdint.h>
#include "Screen.h"
#include "Screen_Color.h"
#include "Common_SPI.h"
#include "Common_IO.h"

class Screen_16bitColor_SPI : public Screen<Color_16bit>
{
public:
  Screen_16bitColor_SPI(int _dev, int cs_port, int cs_pin, int rst_port, int rst_pin, int dc_port, int dc_pin, int width, int height)
      : Screen(width, height), dev(_dev, cs_port, cs_pin), rst(rst_port, rst_pin), dc(dc_port, dc_pin) {}

  void init();
  void write_data(uint16_t data);
  void write_data8(uint8_t data);
  void write_reg(uint8_t data);

protected:
  OutPin rst;

private:
  SPI_Dev dev;
  OutPin dc;
};

#endif
