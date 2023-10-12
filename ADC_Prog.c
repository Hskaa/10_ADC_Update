/******************************************************************/
/******************************************************************/
/***************   		Author : Hossam Medhat		***************/
/***************   		Layer : HAL         		***************/
/***************   		SWC : ADC            		***************/
/***************   		Version : 1.00      		***************/
/******************************************************************/
/******************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "ADC_Cfg.h"
#include "ADC_Reg.h"

static u8 *ADC_pu8Reading = NULL;

static void (*ADC_pvCallBackNotificationFunc)(void) = NULL;
u8 ADC_u8BusyState =IDLE;
void ADC_voidInit(void)
{
	/*AVCC as reference voltage*/
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);

	/*Activate left adjust result*/
	SET_BIT(ADMUX,ADMUX_ADLAR);

	/*Set Prescaler tp divide by 128*/
	SET_BIT(ADCSRA,ADCSRA_ADPS2);
	SET_BIT(ADCSRA,ADCSRA_ADPS1);
	SET_BIT(ADCSRA,ADCSRA_ADPS0);

	/*Enable peripheral*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}

u8 ADC_u8StartConversionSynch(u8 Copy_u8channel,u8* Copy_pu8Reading)
{
	u32 Local_u32Counter = 0;
	u8 Local_u8ErrorState = OK;

	if (ADC_u8BusyState==IDLE)
	{
		ADC_u8BusyState=BUSY;

		/*Clear the MUX bits in ADMUX register*/
		ADMUX &=0b11100000;

		/*Set the required channel into the MUX bits*/
		ADMUX |= Copy_u8channel;

		/*Start conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);

		/*Polling (busy waiting) until the conversion complete flag is set*/
		while (((GET_BIT(ADCSRA , ADCSRA_ADPS0))==0) &&(Local_u32Counter != ADC_u32TIMEOUT))
		{
			Local_u32Counter++;
		}

		if (Local_u32Counter== ADC_u32TIMEOUT)
		{
			/*Loop is broken because the timeout is reached*/
			Local_u8ErrorState = NOK;
		}
		else
		{
			/*Loop is broken because flag is raised*/
			/*Clear the conversion complete flag*/
			SET_BIT(ADCSRA,ADCSRA_ADIF);

			/*Return the reading*/
			*Copy_pu8Reading=ADCH;
		}
	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;
	}

	return Local_u8ErrorState;
}



u8 ADC_u8StartConversionAsynch(u8 Copy_u8channel,u8* Copy_pu8Reading , void (*Copy_pvNotufucationFunc)(void))
{
	u8 Local_u8ErrorState =OK;

	if (ADC_u8BusyState==IDLE)
	{
		if((Copy_pu8Reading ==NULL) || (Copy_pvNotufucationFunc == NULL))
		{
			Local_u8ErrorState = NULL_POINTER;
		}
		else
		{
			ADC_u8BusyState = BUSY;
			/*Initialize the reading variable globally*/
			ADC_pu8Reading =Copy_pu8Reading;

			/*Initialize the callback notification func globally*/
			ADC_pvCallBackNotificationFunc = Copy_pvNotufucationFunc ;

			/*Clear the MUX bits in ADMUX register*/
			ADMUX &=0b11100000;

			/*Set the required channel into the MUX bits*/
			ADMUX |= Copy_u8channel;

			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*ADC interrupt enable*/
			SET_BIT(ADCSRA , ADCSRA_ADIE);
		}
	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;
	}

	return Local_u8ErrorState;
}


void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{
	/*Read ADC result*/
	*ADC_pu8Reading=ADCH;

	/*Make ADC state be IDLE because it finished*/
	ADC_u8BusyState=IDLE;

	/*Invoke the callback notification function*/
	ADC_pvCallBackNotificationFunc();

	/*Disable ADC conversion complete interrupt*/
	CLR_BIT(ADCSRA,ADCSRA_ADIE);
}
