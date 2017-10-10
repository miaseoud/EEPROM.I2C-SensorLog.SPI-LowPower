/*----------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------UART Driver AVR------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------*/
#include "UART_AVR.h"
void UART_init () {
  /*UCSRA,B,C are initialized as 0x00 */
  //Setting BAUD rate
  UBRRL = (uint8_t) (FOSC / 16 / BAUD - 1); //low 8 bits of the UBRR
  UBRRH = (uint8_t) ((FOSC / 16 / BAUD - 1) >> 8); //high 4 bits of the UBRR
  UCSRB |=   (1 << RXEN) | (1 << TXEN); //Enable RX and TX
  UCSRC |=   (1 << UCSZ0) | (1 << UCSZ1); //Setting Mode:Frame with 8 bit data, 1 stop bit, no parity UCSZn1 UCSZn0 & Asynchronous mode
}
/*----------------------------------------------------------------------------------------------------------------------*/
void UART_Transmit(uint8_t data) {
  while ( !( UCSRA & (1 << UDRE)) ) ; // wait until the buffer is empty UDREn
  UDR = data;
}
/*----------------------------------------------------------------------------------------------------------------------*/
uint8_t UART_Read() {
  while ( !(UCSRA & (1 << 7)) ) ; //wait until the receiving complete RXCn
  return UDR;
}
/*----------------------------------------------------------------------------------------------------------------------*/
void UART_SendString(char * str) {
  int i = 0 ;
  while (str[i] != 0)
    UART_Transmit(str[i++]);
}
/*----------------------------------------------------------------------------------------------------------------------*/
void UART_ReadString(char* str) {
  char c = 1;
  int i = 0;
  while (c != '\r') {
    c = UART_Read();
    str[i++] = c;
  }
  str[i] = 0 ;
}
/*----------------------------------------------------------------------------------------------------------------------*/
