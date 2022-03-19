#ifndef __COMMON_IIC_H
#define __COMMON_IIC_H

#include <nuclei_sdk_soc.h>
#include <stdint.h>

class IIC_Dev
{
public:
  IIC_Dev(int _dev) : dev(_dev)
  {
  }

private:
  int dev;
};

#endif
