#include <avr/io.h>
#include <avr/delay.h>
#include "itoaX.h"
#include "UART_AVR.h"
#include "SPI.h"

#define F_CPU 4000000UL
char str[];

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
  }
}

