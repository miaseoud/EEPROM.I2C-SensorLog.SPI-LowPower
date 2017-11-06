/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------EEPROM(I2C) data logging for SPI Sensor in Power Saving Mode with UART debugging -----------------------*/
/*------------------------------------------------------------------------------------------------------------------------------------------*/
/*Code tested for AVR Atmega32
- The code sets the AVR in power-save mode and relies on external oscillator for asynchronous timer interrupt. 
- Every timer ISR, the microcontroller reads the ith slot from the EEPROM using I2C.
- After reading EEPROM, an SPI communication is performed with TC72 temperature sensor to wake the sensor, get the reading then set it to sleep again.
- The received value is then stored in ith EEPROM slot.
- Sensor and EEPROM readings are returned using UART for debugging.

Libraries/drivers developed:
1. AVR SPI.
2. AVR UART.
3. AVR I2C
4. EEPROM
5. TC72 Temperature Sensor
6. itoa function to Convert (int) into a string for UART transmission of readings.
*/
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h> 
/*----------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------My Libraries-------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
#include "UART_AVR.h"
#include "SPI.h"
#include "I2C_AVR.h"
#include "TIMER2.h"
#include "EEPROM.h"
#include "itoaX.h"
/*----------------------------------------------------------------------------------------------------------------------*/
#define F_CPU 4000000UL
char str[]; //for (int) to string function
uint8_t slot=0; //EEPROM Slot
/*----------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------Main--------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
int main(void) {
/*----------------------------------------------------------Initializations ----------------------------------------------*/
    UART_init();
    SPI_MasterInit();
	I2C_Init();
	Timer2_Async_Init (0);//Count from base (0)
/*-------------------------------------------------------------UART TEST---------------------------------------------------*/
    UART_SendString("UART Echo Test - Enter character:");
    UART_Println() ;
    //UART Echo Test: Read what was transmitted
    UART_Transmit(UART_Read());
    UART_Println() ;
/*----------------------------------------------------------------------------------------------------------------------------*/	
	Timer2_OV_InterruptEnable (); 
	sei(); // Master Enable Interrupts
	MCUCR=1<<SM1 | 1<<SM0; //Set AVR in Power Save Mode

/*----------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------Super Loop------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------*/
    while (1) {
		MCUCR|=1<<SE; //Sleep Enable  		
	}
}
/*---------------------------------------------In Power-Save mode asynchronous timer ISR-----------------------------------------*/
ISR(TIMER2_OVF_vect) {
		uint8_t val;
        val= (int)ReadByte(EPROM_READ_ADR);
        UART_SendString("EEPROM Reading:\r\n");
        UART_SendString(itoaX(val, str, 10));////print received value in UART for debugging
        UART_Println() ;
//One shot operation allows waking the sensor and reading once. Other operations such continuous reading are available in the driver.
		val=TC72Read_OneShot();
        UART_SendString("Sensor Reading:\r\n");
        UART_SendString(itoaX(val, str, 10));//print received value in UART for debugging
        UART_Println() ;
	    TC72Set_ShutDown();//Send the sensor back to sleep
	  
	    WriteByte(EPROM_WRITE_ADR, slot , val);//Write value to EEPROM slot
		UART_Println() ;
		slot++; //Next slot location. The unsigned 8 bit variable overflows after 255 matching the EEPROM size.
}  
/*----------------------------------------------------------------------------------------------------------------------------*/