#include <nuclei_sdk_soc.h>
#include <stdint.h>
#include "Common_SPI.h"

void SPI_Dev::init()
{
  spi_parameter_struct spi;
  spi.trans_mode = SPI_TRANSMODE_FULLDUPLEX;
  spi.device_mode = SPI_MASTER;
  spi.frame_size = SPI_FRAMESIZE_8BIT;
  spi.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
  spi.nss = SPI_NSS_SOFT;
  spi.prescale = SPI_PSC_8;
  spi.endian = SPI_ENDIAN_MSB;

  spi_init(dev, &spi);
  spi_crc_polynomial_set(dev, 7);
  spi_enable(dev);

  cs.init();
}

void SPI_Dev::write_byte(uint8_t data)
{
  cs.clr();

  spi_i2s_data_transmit(dev, data);
  while (spi_i2s_flag_get(dev, SPI_FLAG_TBE) == RESET)
    ;

  cs.set();
}