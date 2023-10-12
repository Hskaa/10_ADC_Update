/******************************************************************/
/******************************************************************/
/***************   		Author : Hossam Medhat		***************/
/***************   		Layer : HAL         		***************/
/***************   		SWC : LCD           		***************/
/***************   		Version : 1.00      		***************/
/******************************************************************/
/******************************************************************/


#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_Interface.h"

#include "LCD_Interface.h"
#include "LCD_Cfg.h"
#include "LCD_Private.h"


void LCD_voidSendCommand(u8 Cpy_u8Command)
{
	/* Set RS to low for command */
	DIO_u8SetPinValue(LCD_CTRL_PORT , LCD_RS_PIN , DIO_LOW);

	/* Set RW to low for write */
	DIO_u8SetPinValue(LCD_CTRL_PORT , LCD_RW_PIN , DIO_LOW);

	/* Set command to data pins */
	DIO_u8SetPortValue(LCD_DATA_PORT , Cpy_u8Command);

	/*Send enable pulse */
	DIO_u8SetPinValue(LCD_CTRL_PORT , LCD_E_PIN , DIO_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_CTRL_PORT , LCD_E_PIN , DIO_LOW);

}

void LCD_voidSendData(u8 Cpy_u8Data)
{
	/* Set RS to high for data */
	DIO_u8SetPinValue(LCD_CTRL_PORT , LCD_RS_PIN , DIO_HIGH);

	/* Set RW to low for write */
	DIO_u8SetPinValue(LCD_CTRL_PORT , LCD_RW_PIN , DIO_LOW);

	/* Set data to data pins */
	DIO_u8SetPortValue(LCD_DATA_PORT , Cpy_u8Data);

	/*Send enable pulse */
	DIO_u8SetPinValue(LCD_CTRL_PORT , LCD_E_PIN , DIO_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(LCD_CTRL_PORT , LCD_E_PIN , DIO_LOW);
}

void LCD_voidInit(void)
{
	/*wait for more than 30 ms*/
	_delay_ms(40);

	/*Function set command 2 lines , 5*8 font size*/
	LCD_voidSendCommand(0b00111000);

	_delay_ms(1);

	/*Display on off control : display enable , disblay cursor , display blink */
	LCD_voidSendCommand(0b00001100);

	_delay_ms(1);
	/*Clear display*/
	LCD_voidSendCommand(1);

    _delay_ms(2);

	/*Entry Mode Set*/
	LCD_voidSendCommand(0b00000110);

}

void LCD_voidSendString (const char * Cpy_pcString)
{
	u8 Local_u8Counter = 0;
	while (Cpy_pcString[Local_u8Counter]!='\0')
	{
		LCD_voidSendData(Cpy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}
}

void LCD_voidGoToXY(u8 Cpy_u8XPos ,u8 Cpy_u8YPos  )
{
	u8 Local_u8Address;
	if (Cpy_u8XPos==0)
	{
		/*Writing in first line*/
		Local_u8Address = Cpy_u8YPos;
	}
	else if (Cpy_u8XPos==1)
	{
		/*Writing in second line*/
		Local_u8Address = Cpy_u8YPos+0x40;
	}
	LCD_voidSendCommand(Local_u8Address+128);
}


void LCD_voidWriteSpecialCharacter(u8* Cpy_u8Pattern , u8 Cpy_u8PatternNumber ,u8 Cpy_u8XPos , u8 Cpy_u8YPos)
{
	u8 Local_u8CGRAMAddress=0,Local_u8Iterator;
	/*Calculate the CG RAM address whose its block is 8 bytes*/
	Local_u8CGRAMAddress = Cpy_u8PatternNumber*8;

	/*Send CG RAM address command to LCD , with wetting bit 6 , clearing bit 7*/
	LCD_voidSendCommand(Local_u8CGRAMAddress+64);

	/*Write the pattern into CG RAM*/
	for(Local_u8Iterator=0;Local_u8Iterator<8;Local_u8Iterator++)
	{
		LCD_voidSendData(Cpy_u8Pattern[Local_u8Iterator]);
	}
	/*Go to the DD RAM to display the pattern*/
	LCD_voidGoToXY(Cpy_u8XPos,Cpy_u8YPos);

	/*Display the pattern in the CG RAM */
	LCD_voidSendData(Cpy_u8PatternNumber);

}

void LCD_voidClearLCD(void){
	LCD_voidSendCommand(0b00000001);

}

void LCD_voidSendNumber(u8* str){
	u8 index;
	for (index=0 ; str[index]!='\0';index++) // '\0' It expresses to NULL the end of string
	{
		LCD_voidSendData(str[index]);
	}

}

void LCD_voidWriteNumber (u32 Cpy_u32Num)
{
	u8 buffer [16];
	sprintf(buffer , "%d", Cpy_u32Num);       //convert num to string
	for(u32 i =0 ; buffer[i]!='\0';i++)
	{
		LCD_voidSendData(buffer[i]);
	}
}

