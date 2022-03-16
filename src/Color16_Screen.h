#ifndef __Color16_Screen_H
#define __Color16_Screen_H

#include <stdint.h>

enum Color16 : uint16_t
{
    WHITE = 0xFFFF,
    BLACK = 0x0000,
    BLUE = 0x001F,
    BRED = 0XF81F,
    GRED = 0XFFE0,
    GBLUE = 0X07FF,
    RED = 0xF800,
    MAGENTA = 0xF81F,
    GREEN = 0x07E0,
    CYAN = 0x7FFF,
    YELLOW = 0xFFE0,
    BROWN = 0XBC40,
    BRRED = 0XFC07, // maroon
    GRAY = 0X8430,

    DARKBLUE = 0X01CF,
    LIGHTBLUE = 0X7D7C,
    GRAYBLUE = 0X5458,

    LIGHTGREEN = 0X841F,
    LGRAY = 0XC618,
    LGRAYBLUE = 0XA651,
    LBBLUE = 0X2B12,
};

class Color16_Screen
{
public:
    Color16_Screen(int width1, int height1) : width(width1), height(height1) {}

    // send command sequence for location (chip related: ST7735...)
    virtual void addr_set(int x1, int y1, int x2, int y2) {}

    // write color data (protocol related: I2C, SPI...)
    virtual void write_data(uint16_t data) {}

    void fill(int x1, int y1, int x2, int y2, Color16 color);
    void clear(Color16 color);

    void draw_point_big(int x, int y, Color16 color);
    void draw_point(int x, int y, Color16 color);
    void draw_line(int x1, int y1, int x2, int y2, Color16 color);
    void draw_rectangle(int x1, int y1, int x2, int y2, Color16 color);

    // helper for drawing circle
    void draw_point_x(int x, int y, int a, int b, Color16 color);
    void draw_circle(int x, int y, int r, Color16 color);

private:
    void write_bus(uint8_t data);

    int width;
    int height;
};

#endif
