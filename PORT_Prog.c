/******************************************************************/
/******************************************************************/
/***************   		Author : Hossam Medhat		***************/
/***************   		Layer : MCAL         		***************/
/***************   		SWC : PORT            		***************/
/***************   		Version : 1.00      		***************/
/******************************************************************/
/******************************************************************/

#include "STD_TYPES.h"

#include "PORT_Cfg.h"
#include "PORT_Private.h"
#include "PORT_Interface.h"
#include "PORT_Reg.h"


void PORT_voidInit(void)
{
	DDRA=PORTA_DIR;
	DDRB=PORTB_DIR;
	DDRC=PORTC_DIR;
	DDRD=PORTD_DIR;


	PORTA=PORTA_INITIAL_VALUE;
	PORTB=PORTB_INITIAL_VALUE;
	PORTC=PORTC_INITIAL_VALUE;
	PORTD=PORTD_INITIAL_VALUE;
}




