#ifndef __SSD1306_H
#define __SSD1306_H

/**
 * SSD1306 is a 128 x 64 Dot Matrix OLED/PLED Segment/Common Driver with Controller
 */

#include <stdint.h>
#include "Screen.h"
#include "Screen_Color.h"
#include "Common_SPI.h"
#include "Common_IIC.h"

class Screen_SSD1306 : public Screen<Color_1bit>
{
public:
    Screen_SSD1306(int width, int height) : Screen(width, height) {}

    void display_on();
    void display_off();
    void set_brightness(uint8_t value);
    void up_down_invert();
    void color_reverse();

    void draw_point(int x, int y, Color_1bit color) override;

protected:
    void send_init_commands();

private:
    virtual void write_data(uint8_t data) {}
    virtual void write_cmd(uint8_t cmd) {}
    virtual void write_cmd(uint8_t cmd, uint8_t param) {}

    uint8_t buf[128][8];
    int direction = 0;
};

class Screen_SSD1306_IIC : public Screen_SSD1306
{
public:
    Screen_SSD1306_IIC(int _dev, int addr, int width, int height)
        : Screen_SSD1306(width, height), dev(_dev, addr) {}

    void init();

private:
    void write_data(uint8_t data) override;
    void write_cmd(uint8_t cmd) override;
    void write_cmd(uint8_t cmd, uint8_t param) override;

    IIC_Dev dev;
};

#endif
