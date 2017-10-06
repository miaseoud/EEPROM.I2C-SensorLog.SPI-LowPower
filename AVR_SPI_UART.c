#include <avr/io.h>
#include <avr/delay.h>
#include "itoa.h"

#define F_CPU 4000000UL
#define FOSC 4000000
#define BAUD 9600

#define DDR_SPI DDRB
#define PORT_SPI PORTB
#define DD_MOSI 5
#define DD_MISO 6
#define DD_SCK 7
#define DD_SS 4

#define UART_Println()   UART_SendString("\r\n")
#define SPI_SS_RELEASE() PORTB |= 1 << 4
#define SPI_SS_HOLD() PORTB &= ~(1 << 4)
char str[];
/*
char* itoaX(int num, char* str, int base) {
  int i = 0; //index of the string
  char neg = 0;
  int rem;
  // to handle number=0 case
  if (num == 0) {
    str[i] = '0';
    str[i + 1] = '\0';
    return str;
  }
  // Standard "itoa" only handles negative numbers in base 10. Number with other bases are considered unsigned.
  if (num < 0 && base == 10) {
    neg = 1; //Flag
    //To positive for conversion to string using modulus
    num = -num;
  }

  //Conversion from number to string characters using base-x modulus followed by base division
  while (num != 0) {
    rem = num % base;
    //For base such 16 hex
    if (rem > 9) {
      str[i] = (rem - 10) + 'a';
    }
    else {
      str[i] = rem + '0';
    }
    num = num / base;
    i++; //Moving to the next string cell.
  }
  // If number with base 10 is negative, add '-' at the end of string.
  if (neg) {
    str[i++] = '-';
  }
  str[i] = '\0'; // add string null terminator
  // Reverse the string
  reverse_string(str);
  return str;
}

void reverse_string(char *str) {
  int len;
  for (len = 0; str[len] != '\0'; len++);
  char temp, i;
  for (i = 0; i < len / 2; i++) {
    temp = str[i];
    str[i] = str[len - i - 1];
    str[len - 1 - i] = temp;
  }
}
*/
void UART_init () {
  /*UCSRA,B,C are initialized as 0x00 */
  //Setting BAUD rate
  UBRRL = (uint8_t) (FOSC / 16 / BAUD - 1); //low 8 bits of the UBRR
  UBRRH = (uint8_t) ((FOSC / 16 / BAUD - 1) >> 8); //high 4 bits of the UBRR
  UCSRB |=   (1 << RXEN) | (1 << TXEN); //Enable RX and TX
  UCSRC |=   (1 << UCSZ0) | (1 << UCSZ1); //Setting Mode:Frame with 8 bit data, 1 stop bit, no parity UCSZn1 UCSZn0 & Asynchronous mode
}

void UART_Transmit(uint8_t data) {
  while ( !( UCSRA & (1 << UDRE)) ) ; // wait until the buffer is empty UDREn
  UDR = data;
}
uint8_t UART_Read() {
  while ( !(UCSRA & (1 << 7)) ) ; //wait until the receiving complete RXCn
  return UDR;
}

void UART_SendString(char * str) {
  int i = 0 ;
  while (str[i] != 0)
    UART_Transmit(str[i++]);
}

void UART_ReadString(char* str) {
  char c = 1;
  int i = 0;
  while (c != '\r') {
    c = UART_Read();
    str[i++] = c;
  }
  str[i] = 0 ;
}

void SPI_MasterInit(void){
  /* Set MOSI and SCK output, all others input */
  DDR_SPI = (1 << DD_SCK) | (1 << DD_SS) | (1 << DD_MOSI) ;
  // DDR_SPI &= ~((1<<DD_MISO) ;
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); ///Enable SPI, Set as Master, clock rate fck/16
}
char SPI_MasterTransmit(char cData){

  SPDR = cData;/* Start transmission */
  while (!(SPSR & (1 << SPIF))); // Wait for transmission to complete: When a serial transfer is complete, the SPIF Flag is set
  return SPDR;
}

int main(void) {
  int val;
  UART_init();
  SPI_SS_RELEASE();
  SPI_MasterInit();
  //UART Echo Test
  UART_SendString("UART Echo Test - Enter character:");
  UART_Println() ;
  UART_Transmit(UART_Read());
  UART_Println() ;

  while (1) {
    UART_Read();
    SPI_SS_HOLD();
    val = SPI_MasterTransmit(0) << 5;
    val = val | SPI_MasterTransmit(0) >> 3;
    SPI_SS_RELEASE();
    UART_SendString(itoaX(val * 0.0625, str, 10));
    UART_Println() ;


    SPI_SS_HOLD();
    SPI_MasterTransmit(0xFF);
    SPI_MasterTransmit(0xFF);
    SPI_SS_RELEASE();
    UART_Read();
    SPI_SS_HOLD();
    val = SPI_MasterTransmit(0xFF) << 5;
    val = val | SPI_MasterTransmit(0xFF) >> 3;
    SPI_SS_RELEASE();
    UART_SendString(itoaX(val * 0.0625, str, 10));
    UART_Println() ;
	
	SPI_SS_HOLD();
    val = SPI_MasterTransmit(0xFF) << 5;
    val = val | SPI_MasterTransmit(0xFF) >> 3;
    SPI_SS_RELEASE();
    UART_SendString(itoaX(val * 0.0625, str, 10));
    UART_Println() ;
  }
}

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