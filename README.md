
## EEPROM(I2C) data logging for SPI Sensor in Power Saving Mode with UART debugging
Code tested for AVR Atmega32
- The code sets the AVR in power-save mode and relies on external oscillator for asynchronous timer interrupt. 
- Every timer ISR, the microcontroller reads the ith slot from the EEPROM using I2C.
- After reading EEPROM, an SPI communication is performed with TC72 temperature sensor to wake the sensor, get the reading then set it to sleep again.
- The received value is then stored in ith EEPROM slot.
- Sensor and EEPROM readings are returned using UART for debugging.

### Libraries/peripheral drivers developed:
* AVR I2C
`````
void I2C_Init(void);
`````
`````
void I2C_Start (void);
`````
`````
void I2C_Stop (void);
`````
`````
void I2C_Write (uint8_t data);
`````
`````
uint8_t I2C_Read (void);
`````
`````
uint8_t I2C_GetStatus(void);
`````
* EEPROM I2C (265 byte)
`````
uint8_t WriteByte (uint8_t addr, uint8_t slot, uint8_t data);
`````
`````
uint8_t ReadByte (uint8_t addr);
`````
*  AVR SPI 
```````````````
void SPI_MasterInit(void);
```````````````
```````````````
char SPI_MasterTransmit(char); 
```````````````

* TC72 SPI Temperature Sensor
````
uint8_t TC72Read_OneShot(void);
````
````
uint8_t TC72Read (void);
````
````
void TC72Set_ShutDown(void);
````
````
void TC72Set_Continiuous(void);
````
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
* EEPROM Read & Write addresses in EEPROM.h
* Timer2 counting base as function input.
