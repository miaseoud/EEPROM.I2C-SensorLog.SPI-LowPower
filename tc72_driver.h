#ifndef tc72_driver_H_
#define tc72_driver_H_

typedef unsigned char uint8_t;
uint8_t TC72Read_OneShot(void);
uint8_t TC72Read (void);
void TC72Set_ShutDown(void);
void TC72Set_Continiuous(void);
#endif /* INCFILE1_H_ */