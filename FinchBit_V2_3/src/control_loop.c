/*
 * control_loop.c
 *
 * Created: 9/24/2018 11:54:36 AM
 *  Author: raghu
 */ 

#include <asf.h>
#include "control_loop.h"
#include "motors.h"
#include "encoders.h"


//Globals
extern uint16_t left_encoder_ticks;
extern uint16_t right_encoder_ticks;
static uint16_t left_total_req_ticks = 0;
static uint16_t right_total_req_ticks = 0;
static bool left_dir  = false;
static bool right_dir = false;


volatile uint8_t speed_storage[1000];
//volatile uint8_t sum_integral_storage[255];
//volatile uint8_t diff_derivative_storage[255];
//volatile uint8_t proportional_storage[255];


//Modules
#define NO_TICKS_PER_CM			   7
#define MAX_SPEED_THRESHOLD        15*NO_TICKS_PER_CM
#define MAX_SPEED                 100
#define MINIMUM_SPEED_CONTROL     10
#define KP_CONTROL                1
#define KI_CONTROL                2500
#define KD_CONTROL                2
#define MIN_SPEED                 5


static uint16_t kp_constant = KP_CONTROL;
static uint16_t ki_constant = KI_CONTROL;
static uint16_t kd_constant = KD_CONTROL;


void control_loop_motors()
{
	volatile uint8_t speed = 0;
	
	static uint16_t k =0;
	uint16_t temp_speed = 0;
	
	static uint32_t sum_integral_left = 0;
	static uint16_t  prev_error_left   = 0;
	
	static uint32_t sum_integral_right = 0;
	static uint16_t  prev_error_right   = 0;
	
	uint16_t  current_error   = 0;
	volatile int16_t   diff_derivative = 0; 
	static bool first_time = false;
	if(first_time == false);
	{
		first_time = true ; 
		prev_error_left  = abs(left_total_req_ticks - left_encoder_ticks) ;
		prev_error_right = abs(right_total_req_ticks - right_encoder_ticks) ;
	}
	//Left Motor
	if((left_encoder_ticks - left_total_req_ticks) >= 0)
	{
		port_pin_set_output_level(PROFILE_PIN,true);
		set_motor_left(left_dir ,  0);
		port_pin_set_output_level(PROFILE_PIN,false);
		//delay_cycles_ms(2000);
		//move_motor(true , 128 , true , 0);
		sum_integral_left = 0;
		//tc_disable_callback(&tc_encoder_capture, TC_CALLBACK_OVERFLOW);
	}
	else   
	{
		//Proportional control 
		// Integral 
		current_error   = abs(left_total_req_ticks - left_encoder_ticks) ;
		sum_integral_left   +=  current_error;
		if(sum_integral_left > 100 * ki_constant)
		{
			sum_integral_left  =  100 * ki_constant;
		}
		diff_derivative =  (current_error - prev_error_left);
		temp_speed = current_error/kp_constant + sum_integral_left/ki_constant ;//+ diff_derivative/kd_constant ;
		if(temp_speed > 255)
		{
			speed = 255;
		}
		else
		{
			speed = temp_speed;
		}
		
		speed_storage[k] = sum_integral_left/KI_CONTROL ;
		//sum_integral_storage[k] = sum_integral_left/KI_CONTROL ;
		//diff_derivative_storage[k] = diff_derivative/KD_CONTROL ;
		//proportional_storage[k] = current_error/KP_CONTROL;
		
		k++;
		if(k == 1000)
		{
			k=0;
		}
		set_motor_left(left_dir ,  speed);
		prev_error_left  = current_error ;
	}
	
	//Right Motor
	if((right_encoder_ticks - right_total_req_ticks) >= 0)
	{
		set_motor_right(right_dir , 0 );
		sum_integral_right = 0;
	}
	else
	{
		//PID control
		current_error   = abs(right_total_req_ticks - right_encoder_ticks) ;
		sum_integral_right   +=  current_error;
		if(sum_integral_right > 255 * ki_constant)
		{
			sum_integral_right  =  100 * ki_constant;
		}
		diff_derivative =  (current_error - prev_error_right);
		temp_speed = current_error/kp_constant + sum_integral_right/ki_constant + diff_derivative/kd_constant ;
		if(temp_speed > 255)
		{
			speed = 255;
		}
		else
		{
			speed = temp_speed;
		}
		//speed = 15;
		set_motor_right(right_dir ,  speed);
	}
	
	if(((right_encoder_ticks - right_total_req_ticks) >= 0) && ((left_encoder_ticks - left_total_req_ticks) >= 0) )
	{
		set_motor_left(left_dir , 0 );
		//delay_cycles_ms(1000);
		set_motor_right(right_dir , 0 );
		tc_disable_callback(&tc_encoder_capture, TC_CALLBACK_OVERFLOW);
	}
}



void calculate_initial_speed_left()
{
	if(left_total_req_ticks > MAX_SPEED_THRESHOLD)
	{
		set_motor_left(left_dir , MAX_SPEED );
	}
}


void calculate_initial_speed_right()
{
	if(right_total_req_ticks > MAX_SPEED_THRESHOLD)
	{
		set_motor_right(right_dir , MAX_SPEED );
	}
}

void ticks_left()
{
	//calculate_initial_speed_left();
	left_encoder_ticks = 0;
	//tc_enable_callback(&tc_encoder_capture, TC_CALLBACK_OVERFLOW);
	
}

void ticks_right()
{
	//calculate_initial_speed_right();
	right_encoder_ticks = 0;
	//tc_enable_callback(&tc_encoder_capture, TC_CALLBACK_OVERFLOW);
}

void update_PID_values(uint8_t* pid_values )
{
	kp_constant   = (pid_values[0] << 8) & 0xFF00 ;
	kp_constant  |=  pid_values[1];
	
	ki_constant   = (pid_values[2] << 8) & 0xFF00 ;
	ki_constant  |=  pid_values[3];
	
	kd_constant   = (pid_values[4] << 8) & 0xFF00 ;
	kd_constant  |=  pid_values[5];

}

void move_motor(bool left_direction , uint16_t left_ticks, bool right_direction , uint16_t right_ticks)
{
	if((left_ticks > 0) || (right_ticks > 0))
	{
		if(left_ticks > 0)
		{
			left_dir  = left_direction;
			left_total_req_ticks = left_ticks;
			ticks_left();
		}
		if(right_ticks > 0)
		{
			right_dir = right_direction;
			right_total_req_ticks = right_ticks;
			ticks_right();
		}
		tc_enable_callback(&tc_encoder_capture, TC_CALLBACK_OVERFLOW);
	}
	//calculate_initial_speed_right();
	//calculate_initial_speed_left();
}
