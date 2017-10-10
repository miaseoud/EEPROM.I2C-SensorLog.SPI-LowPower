/*----------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------SPI Driver AVR------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
#include "SPI.h"
void SPI_MasterInit(void){
  /* Set MOSI and SCK output, all others input */
  DDR_SPI = (1 << DD_SCK) | (1 << DD_SS) | (1 << DD_MOSI) ;
  // DDR_SPI &= ~((1<<DD_MISO) ;
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); ///Enable SPI, Set as Master, clock rate fck/16
}
/**********************************************************************************************************************************************/
char SPI_MasterTransmit(char cData){
  SPDR = cData;/* Start transmission */
  while (!(SPSR & (1 << SPIF))); // Wait for transmission to complete: When a serial transfer is complete, the SPIF Flag is set
  return SPDR;
}
/**********************************************************************************************************************************************/
/**********************************************************************************************************************************************/
//Older Version
/* void SPI_MasterTransmit(char cData) {
  DDR_SPI |= (1 << DD_MOSI) | (1 << DD_MISO); //output
  //DDR_SPI |= (1<<DD_MOSI);
  SPDR = cData;// Start transmission
  while (!(SPSR & (1 << SPIF))); // Wait for transmission to complete: When a serial transfer is complete, the SPIF Flag is set
  }

  char SPI_MasterReceive(void) {
  //DDR_SPI &= ~((1<<DD_MISO) | (1<<DD_MOSI)); //both input (not necessary now with diode)
  SPDR = 0;// Start transmission
  while (!(SPSR & (1 << SPIF))); // Wait for transmission to complete: When a serial transfer is complete, the SPIF Flag is set
  return SPDR;
  }
*/