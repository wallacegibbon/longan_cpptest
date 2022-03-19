#include "Common_SPI.h"

void SPI_Dev::write_byte(uint8_t data)
{
  cs.clr();

  spi_i2s_data_transmit(dev, data);
  while (spi_i2s_flag_get(dev, SPI_FLAG_TBE) == RESET)
    ;

  cs.set();
}