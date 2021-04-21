
#ifndef LED_H_
#define LED_H_
#define PORT_NO DIO_PORTA
#define led1  0
#define led2  1
#define led3  2
extern void HAL_TURN_ON_LED_1();
extern void HAL_TURN_OFF_LED_1();
extern void HAL_TURN_ON_LED_2();
extern void HAL_TURN_OFF_LED_2();
extern void HAL_TURN_ON_LED_3();
extern void HAL_TURN_OFF_LED_3();

#endif /* LED_H_ */
