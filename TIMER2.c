/*-------------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------Timer 2 Driver AVR------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/
//Asynchronous operation using external oscillator and /1024 prescaler
#include <avr/io.h>
#include "TIMER2.h"

void Timer2_Async_Init (uint8_t timer) {
TIMSK &= !((1<<TOIE2) | (1<<OCIE2));//Disable Timer2 interrupts;
 ASSR  |= (1<<AS2); // Set asynchronous Mode
//Dividing 32768 by 128 gives 256: one full counter with overflow interrupt. So we are going to us this. Lets make a simple 1Hz LED flasher.
TCCR2 |= (1<<CS22)|(1<<CS20) ; //Normal Mode
TCNT2= timer;
while ((ASSR & ((1 << TCN2UB)  |  (1 << TCR2UB))));//  A logical zero in this bit indicates that TCCR2/ is ready to be updated with a new value
 TIFR  = (1<<TOV2);//Clear Timer2 Flags
}
/*----------------------------------------------------------------------------------------------------------------------*/
 void Timer2_OV_InterruptEnable (void) {
TIMSK |=(1<<TOIE2);//Overflow Interrupt Enable
 }