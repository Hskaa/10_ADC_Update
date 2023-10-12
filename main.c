#include "STD_TYPES.h"
#include <util/delay.h>

#include "PORT_Interface.h"
#include "DIO_Interface.h"
#include "ADC_Interface.h"
#include "LCD_Interface.h"

void ADCNotification (void);
/*Controlling LEDs with potentiometer ADC*/
u8 App_u8ADCReading;
void main (void)
{
	PORT_voidInit();

	ADC_voidInit();

	GIE_voidEnable();

	while(1)
	{
		ADC_u8StartConversionAsynch(0,&App_u8ADCReading , &ADCNotification);
	}
}

void ADCNotification (void)
{
	DIO_u8SetPortValue(DIO_PORTC , App_u8ADCReading);
}
