/*-------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------I2C EEPROM------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/
#include "I2C_AVR.h"
#include "EEPROM.h"
#include <avr/io.h>
//Writing to EEPROM return SUCCESS or ERROR according to the I2C Status bits.
uint8_t WriteByte(uint8_t addr, uint8_t slot, uint8_t data) {
    I2C_Start();
  if (I2C_GetStatus() != 0x08)    //START
    return ERROR;
    I2C_Write(addr);
if (I2C_GetStatus() != 0x18)     //MT_SLA_ACK
        return ERROR;
    I2C_Write(slot);
     if (I2C_GetStatus() != 0x28)   //MT_DATA_ACK
       return ERROR;
    //write byte to eeprom
    I2C_Write(data);
     if (I2C_GetStatus() != 0x28) // //MT_DATA_ACK
      return ERROR;
    I2C_Stop();
    return SUCCESS;
//ACKNOWLEDGE POLLING
/*Once the Stop condition for a Write
command has been issued, ACK polling
can then be initiated. This involves the
master sending a Start condition followed by the control
byte for a Write command (R/W = 0 ). If the device is still
busy with the write cycle, no ACK will be returned.*/
}

uint8_t ReadByte(uint8_t addr) {
    uint8_t val;
    I2C_Start ();
	if (I2C_GetStatus() != 0x08)    //START
    return ERROR;
    I2C_Write (EPROM_READ_ADR);
    val=I2C_Read ();
    I2C_Stop();
    return val;
}
