/*----------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------SPI Driver AVR------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------*/
#ifndef SPI_H_
#define SPI_H_
#include <avr/io.h>
#define DDR_SPI DDRB //Select Direction Port
#define PORT_SPI PORTB ////Select Output Port
#define DD_MOSI 5 //Select MOSI Pin
#define DD_MISO 6 //Select MISO
#define DD_SCK 7 //Select SCK
#define DD_SS 4 //Select SS
/*-----------------------------------------------------------------------------------------------------------------------*/
#define SPI_SS_RELEASE() PORTB |= 1 << 4
#define SPI_SS_HOLD() PORTB &= ~(1 << 4)
/*---------------------------------------------------Functions declarations-----------------------------------------*/
void SPI_MasterInit(void);
char SPI_MasterTransmit(char cData);
#endif