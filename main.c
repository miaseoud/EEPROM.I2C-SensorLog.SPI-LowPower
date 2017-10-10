/*----------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------SPI Sensor Reading and control + UART Debugging for AVR------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*Code tested for AVR Atmega32
Code uses SPI serial peripheral to communicate with SPI TC77 temperature sensor to read temperature and control sleep function.
Readings are returned using UART for debugging.
Libraries/drivers developed:
1. AVR SPI.
2. AVR UART.
3. itoa function to Convert int into a string for UART transmission of readings.
*/
#include <avr/io.h>
#include <avr/delay.h>
#include "itoaX.h"
/*----------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------My Libraries-------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
#include "UART_AVR.h"
#include "SPI.h"
/*----------------------------------------------------------------------------------------------------------------------*/
#define F_CPU 4000000UL
char str[];
/*----------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------Main-------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
int main(void) {
  int val;
/*---------------------------------------------------------------Initializations -------------------------------------------*/
  UART_init();
  SPI_SS_RELEASE();
  SPI_MasterInit();
/*---------------------------------------------------------------UART TEST-------------------------------------------*/
  UART_SendString("UART Echo Test - Enter character:");
  UART_Println() ;
  //UART Echo Test: Read what was transmitted
  UART_Transmit(UART_Read());
  UART_Println() ;
/*----------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------Super Loop---------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------------------*/
  while (1) {
	//wait for UART entry
    UART_Read();
/*------------------------------------------------------------READ from Sensor------------------------------------------*/
    SPI_SS_HOLD();//chip select enable
	//TC77 Sensor SPI write on MOSI and read to MISO
    val = SPI_MasterTransmit(0) << 5;
    val = val | SPI_MasterTransmit(0) >> 3;
    SPI_SS_RELEASE();//chip select disable
    UART_SendString(itoaX(val * 0.0625, str, 10));//print received value in UART
    UART_Println() ;
/*-----------------------------------------------------------Sensor Sleep--------------------------------------------*/
    SPI_SS_HOLD();//chip select enable
    SPI_MasterTransmit(0xFF);//SPI transmission 
    SPI_MasterTransmit(0xFF);
    SPI_SS_RELEASE();//chip select disable
	//wait for UART entry	
    UART_Read();
	/*-----------------------------------------------------Re-read from sensor-----------------------------------------------*/
    SPI_SS_HOLD();//chip select enable
    val = SPI_MasterTransmit(0xFF) << 5;
    val = val | SPI_MasterTransmit(0xFF) >> 3;
    SPI_SS_RELEASE();//chip select disable
    UART_SendString(itoaX(val * 0.0625, str, 10));
    UART_Println() ;
  }
}

