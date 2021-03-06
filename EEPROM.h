/*-------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------I2C EEPROM------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/
#ifndef EEPROM_H_
#define EEPROM_H_

#define EPROM_WRITE_ADR 0b10100000
#define EPROM_READ_ADR 0b10100001
#define ERROR 1
#define SUCCESS 0

uint8_t WriteByte (uint8_t addr, uint8_t slot, uint8_t data);
uint8_t ReadByte (uint8_t addr);

#endif /* EEPROM_H_ */