

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Compiler.h"

#include "AVR_DIO_REG.h"
#include "DIO_interface.h"

#include "LCD_interface.h"
#include "LCD_PreCFG.h"

#include <avr/delay.h>

/*********************************************************************
 *                    FUNCTIONS DECLERATIONS
 *********************************************************************/
/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Write Command
 * Input     : Copy_u8Command Command
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
static void HAL_LCD_voidWriteCommand(uint8_t Copy_u8Command);
/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Write Data
 * Input     : Copy_u8Data Data To Send
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
static void HAL_LCD_voidWriteData(uint8_t Copy_u8Data);




/*********************************************************************
 *                    FUNCTIONS DEFINITIONS
 *********************************************************************/

/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Write Command
 * Input     : Copy_u8Command Command
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/

/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Write Data
 * Input     : Copy_u8Data Data To Send
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/



/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Initialization
 * Input     : None
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/


/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Write Character
 * Input     : Copy_u8Char (Character To Write on LCD)
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
 void HAL_LCD_voidWriteCharacter(uint8_t Copy_u8Char)
{
	HAL_LCD_voidWriteData(Copy_u8Char); 	/*Write Data To LCD*/
}

 /*_______________________________________________________________________________________________________________________________*/
 /*Description: LCD Write String
  * Input     : ptr_u8String (Pointer to first Character in the String)
  * Output    : None
  *_______________________________________________________________________________________________________________________________*/
 void HAL_LCD_voidWriteString(uint8_t *ptr_u8String)
{
	uint8_t charLoop = START_LOOP;

	while(ptr_u8String[charLoop] != NULL_CHR)
	{
		HAL_LCD_voidWriteData(ptr_u8String[charLoop]);
		charLoop++;
	}
}

 /*_______________________________________________________________________________________________________________________________*/
 /*Description: LCD Move Cursor
  * Input     : Copy_RowNo (Row Number 0 or 1) , Copy_ColNo (Column No. 0 :15 )
  * Output    : None
  *_______________________________________________________________________________________________________________________________*/
void HAL_LCD_MoveCursor(uint8_t Copy_RowNo ,  uint8_t Copy_ColNo)
{
	/*To Move Cursor We Need To Send Command of 0b10000000 + The Address
	 * The Address of First Row Starts From 0x00 and increment with each Column
	 * The Address of Second Row Starts from 0x40 and Increment With Each Column*/
	/*if(Copy_RowNo == 0)
		{
			HAL_LCD_voidWriteCommand( 128 + Copy_RowNo);
		}
		else if(Copy_u8Row == 1)
		{
			HAL_LCD_voidWriteCommand( 128 + 0x40 + Copy_u8Col); //128 = 0x80 = 0b10000000
		}*/
	HAL_LCD_voidWriteCommand(128 + (0x40 * Copy_RowNo) + Copy_ColNo);
}

/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Clear All Screen
 * Input     : None
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void HAL_LCD_voidClearAll(void)
{
	HAL_LCD_voidWriteCommand(0b00000001); /*Clear Command*/
}

/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Clear Part of Screen
 * Input     : Copy_RowNo (Row Number 0 or 1) Copy_u8Start (Start of column to Clear) , Copy_u8End (End Column To clear)
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void HAL_LCD_voidClearPart(uint8_t Copy_RowNo , uint8_t Copy_u8Start , uint8_t Copy_u8End)
{
	uint8_t Local_u8Loop = START_LOOP ;

	HAL_LCD_MoveCursor(Copy_RowNo , Copy_u8Start);

	for(Local_u8Loop = Copy_u8Start ; Local_u8Loop <= Copy_u8End ; Local_u8Loop++)
	{
		HAL_LCD_voidWriteData(' ');
	}
}

/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Display Setup
 * Input     : Copy_u8DisplayValue (Display off or on)
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void HAL_LCD_voidDisplaySetup(uint8_t Copy_u8DisplayValue)
{
	if(Copy_u8DisplayValue == LCD_DISPLAY_ON)
	{
		HAL_LCD_voidWriteCommand(0b00001111); /*0 0 0 0 1 (Display 0 off , 1 on ) (Cursor 0 off 1 on)(Cursor Blink 0 off 1 on)*/
	}
	else if(Copy_u8DisplayValue == LCD_DISPLAY_OFF)
	{
		HAL_LCD_voidWriteCommand(0b00001011); /*0 0 0 0 1 (Display 0 off , 1 on ) (Cursor 0 off 1 on)(Cursor Blink 0 off 1 on)*/
	}
}

/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Cursor Setup
 * Input     : Copy_u8CursorValue (On or Off) , Copy_u8CursorBlink (On or Off)
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void HAL_LCD_voidWriteNumber(uint32_t Copy_u32Number)
{
	uint8_t Local_u8CharArr[10];            /*MAX No. of Integer Digits*/
	uint8_t Local_u8Count=1;               /*Variable to Count Digits*/
	uint8_t Local_u8Count2;
	uint8_t Local_u8Loop=0;
	uint16_t Local_u32IntValue; /*Copy of integer Value as the original Value is not effected*/

	/*We Need To Count Number of Digits in The Number*
	 * _________________________________________________*/


	Local_u32IntValue=Copy_u32Number;

	while(Local_u32IntValue / 10 != 0) /*while there is reminder*/
	{
		Local_u8Count++; /*increase No. of Digits by 1*/

		Local_u32IntValue =	Local_u32IntValue / 10 ; /*Divide it by 10 to decrease Number by digit that is already counted*/
	}
	/*__________________________________________________*/

	/*We Need To Fill The Array with The Number
	 * __________________________________________________*/

	Local_u32IntValue = Copy_u32Number;

	Local_u8Count2 = Local_u8Count;

	while(Local_u8Count!=0)
	{
		Local_u8CharArr[Local_u8Count-1] = Local_u32IntValue % 10;

		Local_u32IntValue /=10;

		Local_u8Count--;
	}
	/*____________________________________________________________*/

	for(Local_u8Loop=0 ; Local_u8Loop < Local_u8Count2 ; Local_u8Loop++)
	{
		HAL_LCD_voidWriteData(Local_u8CharArr[Local_u8Loop] + '0' );  /*Add 48 To each Number To convert To Character*/
	}
}


/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Move Cursor
 * Input     : ptr_Shapes (Pointer to The first Element in special character) , Copy_RowNo (Row Number 0 or 1) , Copy_ColNo (Column No. 0 :15 )
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void HAL_LCD_SpecialChar(uint8_t *ptr_Shapes , uint8_t Copy_RowNo , uint8_t Copy_ColNo)
{
	uint8_t Char_loop ;

	HAL_LCD_voidWriteCommand(0x40);

	for(Char_loop = 0 ; Char_loop < 8 ; Char_loop ++)
	{
		HAL_LCD_voidWriteData(ptr_Shapes[Char_loop]);
	}

	HAL_LCD_MoveCursor(Copy_RowNo , Copy_ColNo);
}



/*
 * LCD_program.c
 *
 *  Created on: Dec 12, 2020
 *      Author: kh
 */

//#include "STD_TYPES.h"
//#include "BIT_MATH.h"
//
//#include "AVR_DIO_REG.h"
//#include "DIO_interface.h"
//
//#include "LCD_interface.h"
//#include "LCD_PreCFG.h"
//
//#include <avr/delay.h>
//
static void HAL_LCD_voidWriteCommand(uint8_t Copy_u8Command);
static void HAL_LCD_voidWriteData(uint8_t Copy_u8Data);

void HAL_LCD_voidWriteCommand(uint8_t Copy_u8Command)
{
#if (LCD_MODE == 8)
	MCAL_DIO_u8SetPinValue(LCD_E_PIN,DIO_LOW);

	MCAL_DIO_u8SetPinValue(LCD_RS_PIN,DIO_LOW); /*RS Command 0 Data 1*/

	MCAL_DIO_u8SetPinValue(LCD_RW_PIN,DIO_LOW); /*RW write  0 Read 1*/

	MCAL_DIO_u8SetPortValue(LCD_DATA_PORT,Copy_u8Command);

	MCAL_DIO_u8SetPinValue(LCD_E_PIN,DIO_HIGH);
	_delay_ms(2);

	MCAL_DIO_u8SetPinValue(LCD_E_PIN,DIO_LOW);
#elif(LCD_MODE == 4)
	MCAL_DIO_u8SetPinValue(LCD_E_PIN,DIO_LOW);

		MCAL_DIO_u8SetPinValue(LCD_RS_PIN,DIO_LOW); /*RS Command 0 Data 1*/

		MCAL_DIO_u8SetPinValue(LCD_RW_PIN,DIO_LOW); /*RW write  0 Read 1*/

		LCD_DATA_PORT_REG = (LCD_DATA_PORT_REG & 0x0f) |(Copy_u8Command & 0xf0) ;

		MCAL_DIO_u8SetPinValue(LCD_E_PIN,DIO_HIGH);

		_delay_ms(2);

		MCAL_DIO_u8SetPinValue(LCD_E_PIN,DIO_LOW);

		_delay_ms(2);

		MCAL_DIO_u8SetPinValue(LCD_E_PIN,DIO_LOW);

		MCAL_DIO_u8SetPinValue(LCD_RS_PIN,DIO_LOW); /*RS Command 0 Data 1*/
		MCAL_DIO_u8SetPinValue(LCD_RW_PIN,DIO_LOW); /*RW write  0 Read 1*/

		LCD_DATA_PORT_REG = (LCD_DATA_PORT_REG & 0x0f) |(Copy_u8Command << 4) ;

	MCAL_DIO_u8SetPinValue(LCD_E_PIN,DIO_HIGH);

	_delay_ms(2);

		MCAL_DIO_u8SetPinValue(LCD_E_PIN,DIO_LOW);

#endif

}

void HAL_LCD_voidWriteData(uint8_t Copy_u8Data)
{
	#if (LCD_MODE == 8)
	MCAL_DIO_u8SetPinValue(LCD_E_PIN,DIO_LOW);

	MCAL_DIO_u8SetPinValue(LCD_RS_PIN,DIO_HIGH); /*RS Command 0 Data 1*/

	MCAL_DIO_u8SetPinValue(LCD_RW_PIN,DIO_LOW); /*RW write  0 Read 1*/

	MCAL_DIO_u8SetPortValue(LCD_DATA_PORT,Copy_u8Data);
		MCAL_DIO_u8SetPinValue(LCD_E_PIN,DIO_HIGH);
		_delay_ms(2);

	MCAL_DIO_u8SetPinValue(LCD_E_PIN,DIO_LOW);
#elif(LCD_MODE == 4)
	MCAL_DIO_u8SetPinValue(LCD_E_PIN,DIO_LOW);

		MCAL_DIO_u8SetPinValue(LCD_RS_PIN,DIO_HIGH); /*RS Command 0 Data 1*/

	MCAL_DIO_u8SetPinValue(LCD_RW_PIN,DIO_LOW); /*RW write  0 Read 1*/

		LCD_DATA_PORT_REG = (LCD_DATA_PORT_REG & 0x0f) |(Copy_u8Data & 0xf0) ;

		MCAL_DIO_u8SetPinValue(LCD_E_PIN,DIO_HIGH);

		_delay_ms(2);

		MCAL_DIO_u8SetPinValue(LCD_E_PIN,DIO_LOW);

		_delay_ms(2);

		MCAL_DIO_u8SetPinValue(LCD_E_PIN,DIO_LOW);

		MCAL_DIO_u8SetPinValue(LCD_RS_PIN,DIO_HIGH); /*RS Command 0 Data 1*/

		MCAL_DIO_u8SetPinValue(LCD_RW_PIN,DIO_LOW); /*RW write  0 Read 1*/

		LCD_DATA_PORT_REG = (LCD_DATA_PORT_REG & 0x0f) |(Copy_u8Data << 4) ;

		MCAL_DIO_u8SetPinValue(LCD_E_PIN,DIO_HIGH);

		_delay_ms(2);

		MCAL_DIO_u8SetPinValue(LCD_E_PIN,DIO_LOW);

#endif

}

void HAL_LCD_voidInit(void)
{
#if (LCD_MODE == 8)
	MCAL_DIO_u8SetPortDir(LCD_DATA_PORT, DIO_PORT_OUTPUT);

	MCAL_DIO_u8SetPinDir(LCD_RS_PIN , DIO_OUTPUT);
	MCAL_DIO_u8SetPinDir(LCD_RW_PIN , DIO_OUTPUT);

	MCAL_DIO_u8SetPinDir(LCD_E_PIN , DIO_OUTPUT);


	_delay_ms(30);

	HAL_LCD_voidWriteCommand(0b00111100); /*0 0 1 (FS : 1 8 bit , 0 4 bit) (N : 0 1_Line , 1 2_Lines ) (Font: 0 5x8 , 1 5x11)*/

	_delay_ms(2);

	HAL_LCD_voidWriteCommand(0b00001111); /*0 0 0 0 1 (Display 0 off , 1 on ) (Cursor 0 off 1 on)(Cursor Blink 0 off 1 on)*/

	_delay_ms(2);

	HAL_LCD_voidWriteCommand(0b00000001); /*Clear Command*/

	_delay_ms(2);

#elif (LCD_MODE == 4)

	MCAL_DIO_u8SetPortDir(LCD_DATA_PORT, DIO_PORT_OUTPUT);
		MCAL_DIO_u8SetPinDir(LCD_RS_PIN , DIO_OUTPUT);

	MCAL_DIO_u8SetPinDir(LCD_RW_PIN , DIO_OUTPUT);

		MCAL_DIO_u8SetPinDir(LCD_E_PIN , DIO_OUTPUT);

		_delay_ms(30);

	HAL_LCD_voidWriteCommand(0x33); /*0 0 1 (FS : 1 8 bit , 0 4 bit) (N : 0 1_Line , 1 2_Lines ) (Font: 0 5x8 , 1 5x11)*/

		_delay_ms(2);

	HAL_LCD_voidWriteCommand(0x32);

		_delay_ms(2);

	HAL_LCD_voidWriteCommand(0b00101100);

		_delay_ms(2);

		HAL_LCD_voidWriteCommand(0b00001111); /*0 0 0 0 1 (Display 0 off , 1 on ) (Cursor 0 off 1 on)(Cursor Blink 0 off 1 on)*/

		_delay_ms(2);

		HAL_LCD_voidWriteCommand(0b00000001); /*Clear Command*/

		_delay_ms(2);

#endif
}









