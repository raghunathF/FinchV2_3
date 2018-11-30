/*
 * power_on_off.c
 *
 * Created: 9/23/2018 11:24:43 AM
 *  Author: raghu
 */ 
#include <asf.h>
#include "power_on_off.h"
#include "status_LED.h"


void init_power_pin()
{
	struct port_config power_button_config;
	port_get_config_defaults(&power_button_config);
	power_button_config.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(POWER_ON_BTN,&power_button_config);
	
	power_button_config.direction  = PORT_PIN_DIR_INPUT;
	power_button_config.input_pull = SYSTEM_PINMUX_PIN_PULL_DOWN;
	port_pin_set_config(POWER_OFF_BTN,&power_button_config);
}


void power_button_on()
{
	port_pin_set_output_level(POWER_ON_BTN, true);
	status_led_red  ( false );
	status_led_green( true );
	//port_pin_set_output_level(RGB_R_PIN, true);
}

void power_off()
{
	volatile static int count_test = 0;
	status_led_green( false );
	status_led_red( true );
	delay_cycles_ms(1000);
	port_pin_set_output_level(POWER_ON_BTN, false);
	count_test = count_test + 1;
	
	
}



void stop_all_actuators()
{
	//RGB LED off
	//Motors off
}

void system_power_off()
{
	//stop_all_actuators();
	power_off();
}

void check_power_off_button()
{
	//volatile uint32_t power_off_button   = 0;
	volatile static uint16_t count_power_button = 0;
	static power_button_value_off = false;
	bool power_button_value = false;
	power_button_value = port_pin_get_input_level(POWER_OFF_BTN);
	//volatile const uint32_t *input_port        = INPUT_REG_ADDRESS;
	//power_off_button = *input_port & MASK_POWER_OFF;
	//if(power_off_button == POWER_OFF_VALUE )
	//{
	if(power_button_value == true)
	{
		count_power_button = count_power_button + 1 ;
		if(count_power_button > POWER_OFF_LIMIT)
		{
			if(power_button_value_off == true)
			{
				system_power_off();
				count_power_button = 0;
			}
			
		}
	}
	else
	{
		count_power_button = 0;
		power_button_value_off = true;
	}
}


void power_button_init()
{
	delay_cycles_ms(2000);
	init_power_pin();
	power_button_on();
}