# SPI Sensor + UART Debugging for AVR
Code tested for AVR Atmega32. The code uses SPI serial peripheral to communicate with SPI TC77 temperature sensor to read temperature and control sleep function.
Readings are returned using UART for debugging.
## Libraries/drivers developed:
*  AVR SPI 
```````````````
void SPI_MasterInit(void);
```````````````
```````````````
char SPI_MasterTransmit(char);  
```````````````
*  AVR UART
```````````````
void UART_init ()
```````````````
``````````````
void UART_Transmit(uint8_t);
``````````````
``````````````
uint8_t UART_Read() 
``````````````
``````````````
void UART_SendString (char *)
``````````````
``````````````
void UART_ReadString (char*) 
``````````````
*  itoa function to Convert int into a string for UART transmission of readings.
```````````````
char* itoaX (int, char*, int);
```````````````

### User Configurations:
* UART baud-rate and system clock in UART.h 
* SPI port: MOSI, MISO, SS & SCLK Pins in SPI.h