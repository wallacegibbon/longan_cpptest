#ifndef __SCREEN_COLOR_H
#define __SCREEN_COLOR_H

#include <stdint.h>

// 5 bit for one color, R + G + B = 15bits, which can be filled into a `short int`

enum Color_16bit : uint16_t
{
  WHITE_16bit = 0xFFFF,
  BLACK_16bit = 0x0000,
  BLUE_16bit = 0x001F,
  BRED_16bit = 0XF81F,
  GRED_16bit = 0XFFE0,
  GBLUE_16bit = 0X07FF,
  RED_16bit = 0xF800,
  MAGENTA_16bit = 0xF81F,
  GREEN_16bit = 0x07E0,
  CYAN_16bit = 0x7FFF,
  YELLOW_16bit = 0xFFE0,
  BROWN_16bit = 0XBC40,
  BRRED_16bit = 0XFC07, // maroon
  GRAY_16bit = 0X8430,

  DARKBLUE_16bit = 0X01CF,
  LIGHTBLUE_16bit = 0X7D7C,
  GRAYBLUE_16bit = 0X5458,

  LIGHTGREEN_16bit = 0X841F,
  LGRAY_16bit = 0XC618,
  LGRAYBLUE_16bit = 0XA651,
  LBBLUE_16bit = 0X2B12,
};

enum Color_1bit : uint8_t
{
  WHITE_1bit = 1,
  BLACK_1bit = 0,
};

#endif
