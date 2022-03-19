#include <stdint.h>
#include "Screen_16bitColor_SPI.h"

void Screen_16bitColor_SPI::init()
{
  dev.init();
  dc.init();
  rst.init();
}

void Screen_16bitColor_SPI::write_data(uint16_t data)
{
  dc.set();
  dev.write_byte(data >> 8);
  dev.write_byte(data);
}

void Screen_16bitColor_SPI::write_data8(uint8_t data)
{
  dc.set();
  dev.write_byte(data);
}

void Screen_16bitColor_SPI::write_cmd(uint8_t data)
{
  dc.clr();
  dev.write_byte(data);
}
