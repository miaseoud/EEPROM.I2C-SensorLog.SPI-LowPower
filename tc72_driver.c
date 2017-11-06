/*-------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------SPI TC72 Sensor Driver------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------------------------*/
#include "tc72_driver.h"
#include "SPI.h"
//#include <avr/delay.h>
//TC72 initial mode is Shut Down with data registers =0
//0x04 for continuous mode,
//0x14 for one shot mode.
//0x14 for one Shutdown mode.
/*-------------------------------------------------------------------------------------------------------------------------------------*/
//Wake sensor and update temperature data register once.
uint8_t TC72Read_OneShot(void) {
    SPI_SS_HOLD();//chip select enable
    SPI_MasterTransmit(0x80);
    SPI_MasterTransmit(0x14);
    SPI_SS_RELEASE();//chip select disable
    return TC72Read();
}
/*-------------------------------------------------------------------------------------------------------------------------------------*/
//Read from data register no matter the sensor is asleep or in continuous-reading mode.
uint8_t TC72Read (void) {
    uint8_t val;
    SPI_SS_HOLD();//chip select enable
    SPI_MasterTransmit(0x02);
    val= SPI_MasterTransmit(0x00)<<1;
    SPI_SS_RELEASE();//chip select disable
    return val;
//SPI_MasterTransmit(0x01);
//val = val | SPI_MasterTransmit(0x00) >> 6;
}
/*-------------------------------------------------------------------------------------------------------------------------------------*/
//-----------------------------------------------------------Sensor Sleep--------------------------------------------
//No temperature update
void TC72Set_ShutDown(void) {
    SPI_SS_HOLD();//chip select enable
    SPI_MasterTransmit(0x80);//SPI transmission
    SPI_MasterTransmit(0x05);
    SPI_SS_RELEASE();//chip select disable
}
/*-------------------------------------------------------------------------------------------------------------------------------------*/
//Update temperature data register continiously
void TC72Set_Continiuous(void) {
    SPI_SS_HOLD();//chip select enable
    SPI_MasterTransmit(0x80);//SPI transmission
    SPI_MasterTransmit(0x04);
    SPI_SS_RELEASE();//chip select disable
}
/*-------------------------------------------------------------------------------------------------------------------------------------*/