#ifndef __COMMON_SPI_H
#define __COMMON_SPI_H

#include <nuclei_sdk_soc.h>
#include <stdint.h>
#include "Common_IO.h"

class SPI_Dev
{
public:
  SPI_Dev(int _dev, int cs_port, int cs_pin) : dev(_dev), cs(cs_port, cs_pin) {}

  void init() { cs.init(); }
  void write_byte(uint8_t data);

private:
  int dev;
  OutPin cs;
};

#endif
