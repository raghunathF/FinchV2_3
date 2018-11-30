/*
 * test.c
 *
 * Created: 9/21/2018 10:21:10 AM
 *  Author: raghu
 */
#include <asf.h>
#include "add_LED_control.h"
#include "motors.h"
#define SIZE_ARRAY_LEDS 9
/*
void test_LED()
{
	uint8_t* leds = NULL;
	leds = malloc(sizeof(uint8_t) * SIZE_ARRAY_LEDS);
	leds[0] = 0x88;
	leds[1] = 0x00;
	leds[2] = 0x00;
	
	leds[3] = 0x88;
	leds[4] = 0x00;
	leds[5] = 0x00;
	
	leds[6] = 0x88;
	leds[7] = 0x00;
	leds[8] = 0x00;
	
	control_LED(leds);
	delay_cycles_ms(1000);
} 
*/
void fadeRED()
{
	volatile static colorInfo test_color;
	uint8_t i = 0;
	test_color.GBrightness = 0;
	test_color.RBrightness = 0;
	test_color.BBrightness = 0;
	for(i=0;i<255;i++)
	{
		test_color.RBrightness = i;
		test_color.GBrightness = i;
		test_color.BBrightness = i;
		RGBPI55SetLED(0,test_color);
		delay_ms(10);
	}
	/*
	for(i=255;i>1;i--)
	{
		test_color.RBrightness = i;
		test_color.GBrightness = i;
		test_color.BBrightness = i;
		RGBPI55SetLED(0,test_color);
		delay_ms(10);
	}
	*/
}
void testADDLED()
{
	fadeRED();
}
void test_motors()
{
	 set_motor_left(1,0);
	 set_motor_right(1,0);
	 delay_cycles_ms(2000);
	 
	 //
	 set_motor_left(1, 100);
	 set_motor_right(1, 0);
	 delay_cycles_ms(2000);
	 /*
	 set_motor_right(1, 100);
	 set_motor_left(1, 0);
	 delay_cycles_ms(2000);
	 //
	 //
	 set_motor_left(1, 255);
	 set_motor_right(1, 0);
	 delay_cycles_ms(2000);
	 
	 set_motor_right(1, 255);
	 set_motor_left(1, 0);
	 delay_cycles_ms(2000);
	 //
	 set_motor_left(1,0);
	 set_motor_right(1,0);
	 delay_cycles_ms(2000);
	 //
	 //
	 set_motor_left(0, 100);
	 set_motor_right(0, 0);
	 delay_cycles_ms(2000);
	 
	 set_motor_right(0, 100);
	 set_motor_left(0, 0);
	 delay_cycles_ms(2000);
	 //
	 //
	 set_motor_left(0, 255);
	 set_motor_right(0, 0);
	 delay_cycles_ms(2000);
	 */
	 set_motor_right(0, 255);
	 set_motor_left(0, 0);
	 delay_cycles_ms(2000);
	 //
}
