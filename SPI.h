#ifndef SPI_H_
#define SPI_H_
#include <avr/io.h>
#define DDR_SPI DDRB
#define PORT_SPI PORTB
#define DD_MOSI 5
#define DD_MISO 6
#define DD_SCK 7
#define DD_SS 4

#define UART_Println() UART_SendString("\r\n")
#define SPI_SS_RELEASE() PORTB |= 1 << 4
#define SPI_SS_HOLD() PORTB &= ~(1 << 4)

void SPI_MasterInit(void);
char SPI_MasterTransmit(char cData);
#endif