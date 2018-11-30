
/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "add_LED.h"
#include "add_LED_control.h"
#include "power_on_off.h"
#include "encoders.h"
#include "test.h"
#include "status_LED.h"

#include "motors.h"
#include "control_loop.h"
#include "spi_slave.h"
#include "spi_slave_control.h"
#include "status_LED.h"

#include "ultraSound.h"
#include "sensorsControl.h"


#include "globals.h"


#define SPI_DATA_LENGTH 20


//SPI related  global variables
void configureProfile()
{
	struct port_config power_button_config;
	port_get_config_defaults(&power_button_config);
	power_button_config.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(PROFILE_PIN,&power_button_config);
	
}

int main (void)
{
	
	system_init();
	delay_init();
	status_led_init();
	power_button_init();
	configure_motors();
	encoders_init();
	spi_slave_init();
	configureUltrasound();
	configureProfile();
	
	//RGBPI55Init();
	
	
	while(1)
	{
		//delay_cycles_ms(10000);
		check_power_off_button();
		readSensors();
		delay_cycles_ms(2);
		spi_main_loop();
		
		//delay_ms(10);
		//delay_cycles_ms(2);
		//testADDLED();
		//test_LED();
		//test_motors();
	}
}
