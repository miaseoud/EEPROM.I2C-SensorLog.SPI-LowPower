#ifndef UART_AVR_H_
#define UART_AVR_H_
#include <avr/io.h>
#define FOSC 4000000
#define BAUD 9600

void UART_init ();

void UART_Transmit(uint8_t data);

uint8_t UART_Read() ;

void UART_SendString(char * str);

void UART_ReadString(char* str) ;

#endif