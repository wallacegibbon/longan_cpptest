#ifndef __SCREEN_ST7735_H
#define __SCREEN_ST7735_H

/**
 * ST7735 is a 132RGB x 162dot 262K Color with Frame Memory Single-Chip TFT Controller/Driver
 */

#include "Screen_16bitColor_SPI.h"

class Screen_ST7735 : public Screen_16bitColor_SPI
{
public:
    Screen_ST7735(int dev, int cs_port, int cs_pin, int rst_port, int rst_pin, int dc_port, int dc_pin, int width, int height)
        : Screen_16bitColor_SPI::Screen_16bitColor_SPI(dev, cs_port, cs_pin, rst_port, rst_pin, dc_port, dc_pin, width, height) {}

    void init();

    void draw_point(int x, int y, Color_16bit color) override;
    void fill(int x1, int y1, int x2, int y2, Color_16bit color) override;

private:
    void send_init_commands();
    void addr_set(int x1, int y1, int x2, int y2);
};

#endif
