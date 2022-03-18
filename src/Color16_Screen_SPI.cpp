#include <nuclei_sdk_soc.h>
#include <stdlib.h>
#include <stdint.h>
#include "Color16_Screen_SPI.h"

void Color16_Screen_SPI::write_bus(uint8_t data)
{
  spi_cs_clr();

  spi_i2s_data_transmit(spi_dev, data);
  while (spi_i2s_flag_get(spi_dev, SPI_FLAG_TBE) == RESET)
    ;

  spi_cs_set();
}

void Color16_Screen_SPI::write_data(uint16_t data)
{
  spi_dc_set();
  write_bus(data >> 8);
  write_bus(data);
}

void Color16_Screen_SPI::write_data8(uint8_t data)
{
  spi_dc_set();
  write_bus(data);
}

void Color16_Screen_SPI::write_reg(uint8_t data)
{
  spi_dc_clr();
  write_bus(data);
}
