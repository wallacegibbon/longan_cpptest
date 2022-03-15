#ifndef __SCREEN_ST7735
#define __SCREEN_ST7735

#include "ScreenColor16_SPI.h"

class Screen_ST7735 : public ScreenColor16_SPI {
public:
	Screen_ST7735(int dev, int rst_port, int rst_pin,
			int cs_port, int cs_pin, int dc_port, int dc_pin,
			int width, int height) :
		ScreenColor16_SPI::ScreenColor16_SPI(
				dev, rst_port, rst_pin, cs_port, cs_pin,
				dc_port, dc_pin, width, height) {
		init();
	}

	void addr_set(int x1, int y1, int x2, int y2) override;
	void init();
};


#endif

