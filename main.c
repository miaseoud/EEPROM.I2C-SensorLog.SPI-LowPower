/*----------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------SPI Sensor Reading and control + UART Debugging for AVR------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*Code tested for AVR Atmega32
- Code uses SPI serial peripheral to communicate with SPI TC72 temperature sensor to read temperature and control sleep function.
- Readings are returned using UART for debugging.
- 
Libraries/drivers developed:
1. AVR SPI.
2. AVR UART.
3. AVR I2C
4. EEPROM
5. TC72 Temperature Sensor
6. itoa function to Convert int into a string for UART transmission of readings.
*/
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h> 
#include "itoaX.h"
/*----------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------My Libraries-------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
#include "UART_AVR.h"
#include "SPI.h"
#include "I2C_AVR.h"
#include "TIMER2.h"
/*----------------------------------------------------------------------------------------------------------------------*/
#define F_CPU 4000000UL
char str[];
volatile uint8_t tot_overflow;
/*----------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------Main--------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
int main(void) {
    int val;
//	tot_overflow = 0;
    /*---------------------------------------------------------------Initializations -------------------------------------*/
    UART_init();
    SPI_MasterInit();
	I2C_Init();
    /*---------------------------------------------------------------UART TEST--------------------------------------------*/
    UART_SendString("UART Echo Test - Enter character:");
    UART_Println() ;
    //UART Echo Test: Read what was transmitted
    UART_Transmit(UART_Read());
    UART_Println() ;
	
Timer2_Async_Init (0);
Timer2_OV_InterruptEnable (); 
sei();
MCUCR=1<<SM1 | 1<<SM0; //Power Save Mode


    /*----------------------------------------------------------------------------------------------------------------------*/
    /*---------------------------------------------------------Super Loop---------------------------------------------------*/
    /*----------------------------------------------------------------------------------------------------------------------*/
    while (1) {
		// UART_SendString("Hi\r\n");
MCUCR|=1<<SE; //Sleep Enable  
       /*
	    //wait for UART entry
        UART_Read();
		val=TC72Read_OneShot();
        UART_SendString("Sensor Reading:\r\n");
        UART_SendString(itoaX(val, str, 10));//print received value in UART
        UART_Println() ;
	  //TC72Set_ShutDown();
		UART_Read();
		val=TC72Read();
        UART_SendString("Sensor Reading 2:\r\n");
        UART_SendString(itoaX(val, str, 10));//print received value in UART
		UART_Println() ;
        //----------------------------------------------------------------------------------------------------------------------
        WriteByte(EPROM_WRITE_ADR, 6 , 72);
        WriteByte(EPROM_WRITE_ADR, 5 , 9);
        val= (int)ReadByte(EPROM_READ_ADR);
        UART_SendString("EEPROM Reading:\r\n");
        UART_SendString(itoaX(val, str, 10));
        UART_Println() ;
		*/
    }
}
ISR(TIMER2_OVF_vect) {
  if (!(tot_overflow++%1)){
 UART_SendString(itoaX(tot_overflow, str, 10));
UART_Println() ;
  }
}  
