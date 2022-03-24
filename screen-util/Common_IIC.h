#ifndef __COMMON_IIC_H
#define __COMMON_IIC_H

#include <stdint.h>
#include "nuclei_sdk_soc.h"

class IIC_Dev
{
public:
    IIC_Dev(int _dev, int _addr) : dev(_dev), addr(_addr << 1) {}

    void init();
    void start_transmit();
    void stop_transmit();
    void write_byte(uint8_t data);

private:
    int dev;
    int addr;
};

#endif
