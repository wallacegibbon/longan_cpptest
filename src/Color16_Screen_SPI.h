#ifndef __Color16_Screen_SPI_H
#define __Color16_Screen_SPI_H

#include <stdint.h>
#include "Color16_Screen.h"

class Color16_Screen_SPI : public Color16_Screen
{
public:
	Color16_Screen_SPI(int dev, int rst_port1, int rst_pin1, int cs_port1, int cs_pin1, int dc_port1, int dc_pin1, int width, int height)
	    : Color16_Screen(width, height),
	      spi_dev(dev), rst_port(rst_port1), rst_pin(rst_pin1),
	      cs_port(cs_port1), cs_pin(cs_pin1), dc_port(dc_port1), dc_pin(dc_pin1) {}

	void spi_rst_set() { gpio_bit_set(rst_port, rst_pin); }
	void spi_rst_clr() { gpio_bit_reset(rst_port, rst_pin); }
	void spi_cs_set() { gpio_bit_set(cs_port, cs_pin); }
	void spi_cs_clr() { gpio_bit_reset(cs_port, cs_pin); }
	void spi_dc_set() { gpio_bit_set(dc_port, dc_pin); }
	void spi_dc_clr() { gpio_bit_reset(dc_port, dc_pin); }

	void write_data(uint16_t data) override;
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
