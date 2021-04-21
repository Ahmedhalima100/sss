/*

 * Masrter.c
 *
 *  Created on: Apr 14, 2021
 *      Author: Halima
 */
#include "CPU_CONFIGURATION.h"
#include "UART_interface.h"
#include "LED.h"
void App_function(uint8_t value);
uint8_t Done=0;
int main(void){
	//intialization
     HAL_LCD_voidInit();
	 MCAL_SPI_SlaveInit();

	 while(1){

	  MCAL_SPI_Slave_DataCallBack(Done,App_function);}}

/**************************************/
void App_function(uint8_t value){
    if(value==1){
       	HAL_TURN_ON_LED_1();}

   else if (value==2){

	    HAL_TURN_OFF_LED_1();}

	else if (value==3){

		HAL_TURN_ON_LED_2();}

	else if (value==4){

		HAL_TURN_OFF_LED_2();}

	else if (value==5){

		HAL_TURN_ON_LED_3();}

	else if (value==6){

		HAL_TURN_OFF_LED_3();}


	}
