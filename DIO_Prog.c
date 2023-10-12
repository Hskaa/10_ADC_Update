/******************************************************************/
/******************************************************************/
/***************   		Author : Hossam Medhat		***************/
/***************   		Layer : MCAL         		***************/
/***************   		SWC : DIO            		***************/
/***************   		Version : 1.00      		***************/
/******************************************************************/
/******************************************************************/
/*****************************************************/
/* 1 - include libraries */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* 2 - include module's files */
#include "DIO_Interface.h"
#include "DIO_Private.h"
#include "DIO_Cfg.h"
#include "DIO_Reg.h"



u8 DIO_u8SetPinValue (u8 Cpy_u8Port , u8 Cpy_u8Pin , u8 Cpy_u8Value){
	u8 Local_u8StateError = 0 ;
	if(Cpy_u8Pin<= DIO_PIN7)
	{
		if (Cpy_u8Value == DIO_INPUT)
		{
			switch (Cpy_u8Port){
			case DIO_PORTA : CLR_BIT(PORTA , Cpy_u8Pin) ; break;
			case DIO_PORTB : CLR_BIT(PORTB , Cpy_u8Pin); break;
			case DIO_PORTC : CLR_BIT(PORTC , Cpy_u8Pin); break;
			case DIO_PORTD : CLR_BIT(PORTD , Cpy_u8Pin); break;
			default: Local_u8StateError = 1; 			break;
			}
		}
		else if (Cpy_u8Value == DIO_OUTPUT){
			switch (Cpy_u8Port){
			case DIO_PORTA : SET_BIT(PORTA , Cpy_u8Pin) ; break;
			case DIO_PORTB : SET_BIT(PORTB , Cpy_u8Pin); break;
			case DIO_PORTC : SET_BIT(PORTC , Cpy_u8Pin); break;
			case DIO_PORTD : SET_BIT(PORTD , Cpy_u8Pin); break;
			default: Local_u8StateError = 1; 			break;
			}
		}
		else{
			Local_u8StateError = 1;
		}
	}
	else {
		Local_u8StateError = 1;
	}

	return Local_u8StateError;
}
u8 DIO_u8GetPinValue (u8 Cpy_u8Port , u8 Cpy_u8Pin){
	u8 local_u8InValue = 0 ;
	switch (Cpy_u8Port){
	case DIO_PORTA : local_u8InValue = GET_BIT(PINA , Cpy_u8Pin) ; break;
	case DIO_PORTB : local_u8InValue = GET_BIT(PINB , Cpy_u8Pin); break;
	case DIO_PORTC : local_u8InValue = GET_BIT(PINC , Cpy_u8Pin); break;
	case DIO_PORTD : local_u8InValue = GET_BIT(PIND , Cpy_u8Pin); break;
	}

	return local_u8InValue ;
}



u8 DIO_u8SetPortValue (u8 Cpy_u8Port , u8 Cpy_u8Value){
	u8 Local_u8StateError =0;
	switch (Cpy_u8Port)
	{
	case DIO_PORTA : PORTA =  Cpy_u8Value; break;
	case DIO_PORTB : PORTB =  Cpy_u8Value; break;
	case DIO_PORTC : PORTC =  Cpy_u8Value; break;
	case DIO_PORTD : PORTD =  Cpy_u8Value; break;
	default: Local_u8StateError = 1;     break;
	}
	return Local_u8StateError ;

}
u8 DIO_u8GetPortValue (u8 Cpy_u8Port){
	u8 local_u8InValue = 0 ;
	switch (Cpy_u8Port){
	case DIO_PORTA : local_u8InValue = PINA ; break;
	case DIO_PORTB : local_u8InValue = PINB ; break;
	case DIO_PORTC : local_u8InValue = PINC ; break;
	case DIO_PORTD : local_u8InValue = PIND ; break;
	}

	return local_u8InValue ;
}
