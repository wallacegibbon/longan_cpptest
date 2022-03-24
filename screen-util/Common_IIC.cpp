#include <stdint.h>
#include "nuclei_sdk_soc.h"
#include "Common_IIC.h"

void IIC_Dev::init()
{
    // i2c_clock_config(dev, 100000, I2C_DTCY_2);
    i2c_clock_config(dev, 400000, I2C_DTCY_2);
    i2c_mode_addr_config(dev, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, addr);
    i2c_enable(dev);
    i2c_ack_config(dev, I2C_ACK_ENABLE);
}

void IIC_Dev::start_transmit()
{
    /* wait until I2C bus is idle */
    while (i2c_flag_get(dev, I2C_FLAG_I2CBSY))
        continue;

    /* send a start condition to I2C bus */
    i2c_start_on_bus(dev);

    /* wait until SBSEND bit is set */
    while (!i2c_flag_get(dev, I2C_FLAG_SBSEND))
        continue;

    /* send slave address to I2C bus */
    i2c_master_addressing(dev, addr, I2C_TRANSMITTER);

    /* wait until ADDSEND bit is set */
    while (!i2c_flag_get(dev, I2C_FLAG_ADDSEND))
        continue;

    /* clear ADDSEND bit */
    i2c_flag_clear(dev, I2C_FLAG_ADDSEND);

    /* wait until the transmit data buffer is empty */
    while (!i2c_flag_get(dev, I2C_FLAG_TBE))
        continue;
}

void IIC_Dev::stop_transmit()
{
    /* send a stop condition to I2C bus */
    i2c_stop_on_bus(dev);

    /* wait until stop condition generate */
    while (I2C_CTL0(dev) & 0x0200)
        continue;
}

void IIC_Dev::write_byte(uint8_t data)
{
    i2c_data_transmit(dev, data);
    while (!i2c_flag_get(dev, I2C_FLAG_TBE))
        continue;
}
