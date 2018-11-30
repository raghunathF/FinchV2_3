/*
 * control_loop.h
 *
 * Created: 9/24/2018 11:56:01 AM
 *  Author: raghu
 */ 


#ifndef CONTROL_LOOP_H_
#define CONTROL_LOOP_H_

void control_loop_motors();
void move_motor(bool left_direction , uint16_t left_ticks, bool right_direction , uint16_t right_ticks);

void update_PID_values(uint8_t* pid_values );

#endif /* CONTROL_LOOP_H_ */