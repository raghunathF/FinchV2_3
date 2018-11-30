/*
 * spi_slave_control.c
 *
 * Created: 9/25/2018 1:55:49 PM
 *  Author: raghu
 */ 
/********************************************************************************************/
#include <asf.h>
#include "spi_slave_control.h"
#include "spi_slave.h"
#include "control_loop.h"
#include "status_LED.h"

/********************************************************************************************/
#define   APP
/********************************************************************************************/

#define PID_TUNING 0x10
#define MOTORS     0xE1

/********************************************************************************************
To ensure that there all the SPI commands that we are waiting for once started takes less than
16 msec to complete we used the timer interrupt of the LED to make it happen.If serial timeout occurred
then reset the SPI so that we have the right SPI bytes in the buffer during the start
********************************************************************************************/
void check_timeout()
{
	
	if(transcation_start == true)
	{
		if(serial_timeout == true)
		{
			serial_timeout_count = 0;
			serial_timeout = false;
			transcation_start = false;
			
			spi_reset(&spi_slave_instance);
			spi_slave_init();
			spi_transceive_buffer_job(&spi_slave_instance, sensor_outputs, received_value,SPI_LENGTH);
		}
	}
}



void spi_main_loop()
{
	
	volatile enum status_code error_code = 0x10;
	volatile static uint16_t count_buffer = 0;
    uint16_t right_encoder_tick_input = 0;
	uint16_t left_encoder_tick_input  = 0;
	uint8_t i    = 0;
	uint8_t rw   = 0;
	uint8_t mode = 0;
	static bool test = true;
	transmit_value[0] = 0x88;
	transmit_value[1] = 0xAA;
	transmit_value[2] = 0xBB;
	transmit_value[3] = 0xCC;
	//check_timeout();
	if(transfer_complete_spi_slave == true)
	{
		check_buffer();
		mode = temp_receive[0];
		switch(mode)
		{
			case PID_TUNING:
				update_PID_values(temp_receive+1);
				break;
			case MOTORS:
				left_encoder_tick_input    = (temp_receive[2]<<8)&0xFF00;
				left_encoder_tick_input   |= (temp_receive[3]);
				right_encoder_tick_input   = (temp_receive[5]<<8)&0xFF00;
				right_encoder_tick_input  |= (temp_receive[6]);
				move_motor(temp_receive[1], left_encoder_tick_input , temp_receive[4] , right_encoder_tick_input);
				break;
			/*
			case RGB1_S:
			update_ORB_single(RGB1_NO , temp_receive[1] , temp_receive[2] , temp_receive[3]);
			break;
				
			case RGB2_S:
			update_ORB_single(RGB2_NO , temp_receive[1] , temp_receive[2] , temp_receive[3]);
			break;
				
			case RGB3_S:
			update_ORB_single(RGB2_NO , temp_receive[1] , temp_receive[2] , temp_receive[3]);
			break;
				
			case MOTOR_SPEED_DISTANCE:
			update_super_servo_single(temp_receive[1],temp_receive[2],temp_receive[3],temp_receive[4],temp_receive[5]);
			break;
				
			case SERVO2_S:
			update_super_servo_single(SERVO2_NO,temp_receive[1]);
			break;

			case SERVO3_S:
			update_super_servo_single(SERVO3_NO,temp_receive[1]);
			break;

			case SERVO4_S:
			update_super_servo_single(SERVO4_NO,temp_receive[1]);
			break;
				
			case SET_ALL:
			update_ORB_LED(temp_receive[3],temp_receive[4] ,temp_receive[5] ,temp_receive[6] ,temp_receive[7] ,temp_receive[8],temp_receive[1],temp_receive[2]);
			update_super_servo(temp_receive[9] , temp_receive[10] , temp_receive[11], temp_receive[12]);
			break;
				
			case STOP_ALL:
			break;
			*/
			default:
				break;
		}	
		check_buffer();	//Look for more SPI commands if occurred , while completing one operation
	}
	
}