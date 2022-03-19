#ifndef __SCREEN_1BITCOLOR_IIC_H
#define __SCREEN_1BITCOLOR_IIC_H

#include <stdint.h>
#include "Screen.h"
#include "Screen_Color.h"
#include "Common_IIC.h"

class Screen_1bitColor_IIC : public Screen<Color_1bit>
{
public:
  Screen_1bitColor_IIC(int _dev, int _addr, int width, int height)
      : Screen(width, height), dev(_dev), addr(_addr) {}

private:
  IIC_Dev dev;
  int addr;
};

#endif
