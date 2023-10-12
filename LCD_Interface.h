/******************************************************************/
/******************************************************************/
/***************   		Author : Hossam Medhat		***************/
/***************   		Layer : HAL         		***************/
/***************   		SWC : LCD           		***************/
/***************   		Version : 1.00      		***************/
/******************************************************************/
/******************************************************************/
#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

void LCD_voidSendCommand(u8 Cpy_u8Command);

void LCD_voidSendData(u8 Cpy_u8Data);

void LCD_voidInit(void);

void LCD_voidSendString (const char * Cpy_pcString);

void LCD_voidGoToXY(u8 Cpy_u8XPos ,u8 Cpy_u8YPos  );

void LCD_voidWriteSpecialCharacter(u8* Cpy_u8Pattern , u8 Cpy_u8PatternNumber ,u8 Cpy_u8XPos , u8 Cpy_u8YPos);

void LCD_voidClearLCD(void);

void LCD_voidSendNumber(u8* str);

void LCD_voidWriteNumber (u32 Cpy_u32Num);

#endif
