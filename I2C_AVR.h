
#ifndef I2C_AVR_H_
#define I2C_AVR_H_
typedef unsigned char uint8_t;
#define F_SCK 10000
//#define EPROM_WRITE_ADR 0b10100000
//#define EPROM_READ_ADR 0b10100001
//#define ERROR 1
//#define SUCCESS 0

void I2C_Init(void);
void I2C_Start (void);
void I2C_Stop (void);
void I2C_Write (uint8_t data);
uint8_t I2C_Read (void);

//uint8_t WriteByte (uint8_t addr, uint8_t slot, uint8_t data);
//uint8_t ReadByte (uint8_t addr);
uint8_t I2C_GetStatus(void);


#endif /* I2C_AVR_H_ */