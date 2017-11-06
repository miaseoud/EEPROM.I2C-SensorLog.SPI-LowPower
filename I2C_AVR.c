/*-------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------I2C Driver------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/
#include "I2C_AVR.h"
#include <avr/delay.h>
#include <avr/io.h>
/*-------------------------------------------------------------------------------------------------------------------------*/
void I2C_Init(void) {
//(read/write the entire memory 00-FF)
    TWSR &=~( (1<<TWPS0) | (1<<TWPS1)); //PreScaler = 1;
    TWBR =(uint8_t) ((F_CPU/F_SCK)-16)/8;
    TWCR |= (1<<TWEN);
}
/*---------------------------------------------------------------Send "Start"-----------------------------------------------*/
void I2C_Start (void) {
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    _delay_ms(50);
}
/*---------------------------------------------------------------Send "Stop"-------------------------------------------------*/
void I2C_Stop (void) {
    TWCR = (1<< TWINT) | (1<<TWSTO)| (1<<TWEN);
}
/*----------------------------------------------------------------I2C Write----------------------------------------------------*/
void I2C_Write (uint8_t data){
    TWDR=data;
    TWCR |= (1<<TWINT) | (1<<TWEN);
   // Wait for TWINT Flag set. This indicates
   // that the DATA has been transmitted, and
   // ACK/NACK has been received
    while (!(TWCR & (1 <<TWINT)));
}
/*-----------------------------------------------------------------I2C read--------------------------------------------------*/
uint8_t I2C_Read (void){
    TWCR |= (1<<TWINT)| (1<<TWEN);
    while (!(TWCR & (1 <<TWINT)));
    return TWDR;
}
/*--------------------------------------------------------------Get I2C status---------------------------------------------------*/
uint8_t I2C_GetStatus(void) {
    //mask and return status
    return (TWSR & 0xF8);
}
/*----------------------------------------------------------------------------------------------------------------------------*/
/*
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
     if (I2C_GetStatus() != 0x28)
      return ERROR;
    I2C_Stop();
    return SUCCESS;
//ACKNOWLEDGE POLLING
//Once the Stop condition for a Write
//command has been issued, ACK polling
//can then be initiated. This involves the
//master sending a Start condition followed by the control
//byte for a Write command (R/W = 0 ). If the device is still
//busy with the write cycle, no ACK will be returned.
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
*/