/*
 * encoders.h
 *
 * Created: 9/21/2018 2:20:17 PM
 *  Author: raghu
 */ 


#ifndef ENCODERS_H_
#define ENCODERS_H_

//Modules initialization
struct  tc_module    tc_encoder_capture;

void encoders_init(void);
void configure_extint_left_encoder(void);
void configure_extint_right_encoder(void);
void configure_extint_left_encoder_callbacks(void);
void configure_extint_right_encoder_callbacks(void);
void encoder_timer_init(void);
void configure_timer_encoder(void);
void init_timer_callbacks(void);



#endif /* ENCODERS_H_ */