/*

 * Masrter.c
 *
 *  Created on: Apr 14, 2021
 *      Author: Halima
 */
#include "CPU_CONFIGURATION.h"
#include "UART_interface.h"
#include "SPI_interface.h"
void send_function(uint8_t value);
void STATUS_OF_LED_MODE(uint8_t value);
int main(void){
	// intialization lcd
	 HAL_LCD_voidInit();
	 //data of UART communication
	str_UartConfg_t1 Data_UART={9600,UART_8_BIT_MODE,UART_INTERRUPT};
	St_SPICfg_t Data_SPI={SPI_MASTER,SPI_MASTER_FREQUENCY_64,SPI_INTERRUPT};
	// intialization UART
	 MCAL_UART_init(&Data_UART);
	 // intialization SPI
	 MCAL_SPI_MasterInit(Data_SPI.ClockFrequency);

     // instructions for users
     HAL_LCD_MoveCursor(0,0);
	 HAL_LCD_voidWriteString("Hello,Sir..");
	    _delay_ms(300);
	 HAL_LCD_voidClearAll();
	 HAL_LCD_MoveCursor(0,0);
	 HAL_LCD_voidWriteString("1 turn on led1");
	    _delay_ms(300);
	 HAL_LCD_voidClearAll();
	 HAL_LCD_voidWriteString("2 turn off led1");
	 	 _delay_ms(300);
	 HAL_LCD_voidClearAll();
	 HAL_LCD_voidWriteString("3 turn on led2");
	 	 _delay_ms(300);
	 HAL_LCD_voidClearAll();
	 HAL_LCD_voidWriteString("4 turn off led2");
	 	  _delay_ms(300);
	 HAL_LCD_voidClearAll();
	 HAL_LCD_voidWriteString("5 turn on led3");
	 	  _delay_ms(300);
	 HAL_LCD_voidClearAll();
	 HAL_LCD_voidWriteString("6 turn off led3");
	 	   _delay_ms(300);
	 HAL_LCD_voidClearAll();
	 while(1){
	   MCAL_UART_RecieveCallBack(send_function);
	     } }
             /****************************/
void send_function(uint8_t value){
	   HAL_LCD_MoveCursor(0,0);
	   HAL_LCD_voidWriteCharacter(value);
	   STATUS_OF_LED_MODE( value);
	 }
void STATUS_OF_LED_MODE(uint8_t value){
switch(value){
    case '1':
        MCAL_SPI_Master_DataCallBack(1,NULL_POINTER);
		HAL_LCD_MoveCursor(0,3);
		HAL_LCD_voidWriteString(": LED1 is on ");
		HAL_LCD_MoveCursor(1,0);
		HAL_LCD_voidWriteString("Order is Done");
		break;
		case '2' :
	    MCAL_SPI_Master_DataCallBack(2,NULL_POINTER);
		HAL_LCD_MoveCursor(0,3);
		HAL_LCD_voidWriteString(": LED1 is Off");
		HAL_LCD_MoveCursor(1,0);
		HAL_LCD_voidWriteString("Order is Done");
		break;
	    case '3':
		 MCAL_SPI_Master_DataCallBack(3,NULL_POINTER);
		 HAL_LCD_MoveCursor(0,3);
		 HAL_LCD_voidWriteString(": LED2 is on ");
		 HAL_LCD_MoveCursor(1,0);
	     break;
	   	  case '4' :
		  MCAL_SPI_Master_DataCallBack(4,NULL_POINTER);
		  HAL_LCD_MoveCursor(0,3);
		  HAL_LCD_voidWriteString(": LED2 is Off");
		  HAL_LCD_MoveCursor(1,0);
		  HAL_LCD_voidWriteString("Order is Done");
		  break;
		  case '5' :
		  MCAL_SPI_Master_DataCallBack(5,NULL_POINTER);
		  HAL_LCD_MoveCursor(0,3);
		  HAL_LCD_voidWriteString(": LED3 is On ");
		  HAL_LCD_MoveCursor(1,0);
		  HAL_LCD_voidWriteString("Order is Done");
		  break;
		  case '6' :
		   MCAL_SPI_Master_DataCallBack(6,NULL_POINTER);
		   HAL_LCD_MoveCursor(0,3);
		   HAL_LCD_voidWriteString(": LED3 is Off");
		   HAL_LCD_MoveCursor(1,0);
		   HAL_LCD_voidWriteString("Order is Done");
		   break;
/****************************************************/

		default :
			   HAL_LCD_voidClearPart(0, 3,15);
			   HAL_LCD_MoveCursor(1,0);
			   HAL_LCD_voidWriteString("Wrong  Access");
			   _delay_ms(200);
			    HAL_LCD_voidClearAll();
}
	}

















