/*
 * status_LED.c
 *
 * Created: 9/23/2018 2:24:46 PM
 *  Author: raghu
 */ 
#include <asf.h>
#include "status_LED.h"
void status_led_init()
{
	//Output initialization
	struct port_config power_button_config;
	port_get_config_defaults(&power_button_config);
	power_button_config.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(BAT_GREEN,&power_button_config);
	port_pin_set_config(BAT_RED,&power_button_config);
	port_pin_set_output_level(BAT_GREEN , false);
	port_pin_set_output_level(BAT_RED , false);
}

void status_led_green(bool on_off)
{
	port_pin_set_output_level(BAT_GREEN , on_off);
}

void status_led_red(bool on_off)
{
	port_pin_set_output_level(BAT_RED , on_off);
}