#ifndef __Color16_Screen_SPI_H
#define __Color16_Screen_SPI_H

#include <nuclei_sdk_soc.h>
#include <stdint.h>
#include "Screen.h"
#include "Color_16bit.h"

class Screen_16bitColor_SPI : public Screen<Color_16bit>
{
public:
  Screen_16bitColor_SPI(int dev, int _rst_port, int _rst_pin, int _cs_port, int _cs_pin, int _dc_port, int _dc_pin, int width, int height)
      : Screen(width, height), spi_dev(dev),
        rst_port(_rst_port), rst_pin(_rst_pin),
        cs_port(_cs_port), cs_pin(_cs_pin),
        dc_port(_dc_port), dc_pin(_dc_pin) {}

  void spi_rst_set() { gpio_bit_set(rst_port, rst_pin); }
  void spi_rst_clr() { gpio_bit_reset(rst_port, rst_pin); }
  void spi_cs_set() { gpio_bit_set(cs_port, cs_pin); }
  void spi_cs_clr() { gpio_bit_reset(cs_port, cs_pin); }
  void spi_dc_set() { gpio_bit_set(dc_port, dc_pin); }
  void spi_dc_clr() { gpio_bit_reset(dc_port, dc_pin); }

  void write_data(uint16_t data);
  void write_data8(uint8_t data);
  void write_reg(uint8_t data);

private:
  void write_bus(uint8_t data);
  int spi_dev;
  int rst_port;
  int rst_pin;
  int cs_port;
  int cs_pin;
  int dc_port;
  int dc_pin;
};

#endif
