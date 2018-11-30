/*
 * add_LED_control.h
 *
 * Created: 9/20/2018 4:54:46 PM
 *  Author: raghu
 */ 


#ifndef ADD_LED_CONTROL_H_
#define ADD_LED_CONTROL_H_

//extern volatile bool transferDone;
//extern volatile uint8_t DMASourceRegister[];

typedef struct
{
	uint8_t RBrightness ;
	uint8_t GBrightness ;
	uint8_t BBrightness ;
}colorInfo;


void RGBPI55SetLED(uint8_t LEDNumber , colorInfo color_led );




#endif /* ADD_LED_CONTROL_H_ */