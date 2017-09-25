/*
 * AVR_SPI_UART.c
 *
 * Created: 2017-09-23 6:11:42 PM
 *  Author: lenovo
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#define F_CPU 4000000UL
#define FOSC 4000000
#define BAUD 9600
#define DDR_SPI DDRB
#define PORT_SPI PORTB
#define DD_MOSI 5
#define DD_MISO 6
#define DD_SCK 7
#define DD_SS 4
void UART_init (){
	/*UCSRA,B,C are initialized as 0x00 */
	UBRRL= (uint8_t) (FOSC/16/BAUD-1); //low 8 bits of the UBRR
	UBRRH= (uint8_t) ((FOSC/16/BAUD-1)>>8); //high 4 bits of the UBRR
	UCSRB |=   (1<<RXEN) | (1<<TXEN);  //Enable RX and TX
	UCSRC |=   (1<<UCSZ0)| (1<<UCSZ1); //Frame with 8 bit data, 1 stop bit, no parity UCSZn1 UCSZn0 & Asynchronous mode 
}

void UART_Transmit(uint8_t data){
    while ( !( UCSRA & (1<<UDRE)) ) ;// wait until the buffer is empty UDREn
	UDR=data;
}
uint8_t UART_Read(){
    while( !(UCSRA & (1<<7)) ) ;//wait until the receiving complete RXCn
	return UDR;
}

void SPI_MasterInit(void){
/* Set MOSI and SCK output, all others input */
DDR_SPI =(1<<DD_SCK)|(1<<DD_SS) ;
SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0); ///Enable SPI, Set as Master, clock rate fck/16 
PORT_SPI &=~((1<<DD_MOSI)|(1<<DD_MISO)) ;
}
char SPI_MasterReceive(void){
	DDR_SPI |= (1<<DD_MOSI);
	DDR_SPI &= ~(1<<DD_MISO);
SPDR = 0;/* Start transmission */
while(!(SPSR & (1<<SPIF)));// Wait for transmission to complete: When a serial transfer is complete, the SPIF Flag is set
return SPDR;
}



int main(void){
	int val;
	DDRA=0xFF;
	PORTA=0x00;
    UART_init();
	PORTB |= 1<<4;
	SPI_MasterInit();
	UART_Transmit(99);	
    while(1) {
      if(UART_Read()=='0'){
	  PORTA=0x00;
	  UART_Transmit(97);
	  }	  
	  else {
	  PORTA=0xFF;
	  UART_Transmit(98);
	  }
	  PORTB &= ~(1<<4);
	  val=SPI_MasterReceive()<<5;
	  val=val | SPI_MasterReceive()>>3;
	  PORTB |= 1<<4;
	  UART_Transmit(val*0.0625);
    }
}