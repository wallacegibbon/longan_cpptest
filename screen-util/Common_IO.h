#ifndef __COMMON_IO_H
#define __COMMON_IO_H

#include <nuclei_sdk_soc.h>

class OutPin
{
public:
  OutPin(int _io_port, int _io_pin) : io_port(_io_port), io_pin(_io_pin) {}

  void init() { gpio_init(io_port, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, io_pin); }
  void set() { gpio_bit_set(io_port, io_pin); }
  void clr() { gpio_bit_reset(io_port, io_pin); }

private:
  int io_port;
  int io_pin;
};

#endif
