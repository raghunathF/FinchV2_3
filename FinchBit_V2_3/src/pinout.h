/*
 * pinout.h
 *
 * Created: 9/20/2018 1:33:31 PM
 *  Author: raghu
 */ 


#ifndef PINOUT_H_
#define PINOUT_H_


#define POWER_ON_BTN		PIN_PA09
#define POWER_OFF_BTN		PIN_PA14

#define BATT_MTR			PIN_PA03
#define BAT_GREEN			PIN_PA30
#define BAT_RED				PIN_PA31

#define AIN1				PIN_PA10
#define AIN2				PIN_PA11
#define BIN1				PIN_PA04
#define BIN2				PIN_PA05

#define ECHO				PIN_PA06
#define TRIG				PIN_PA07

#define PROFILE_PIN          PIN_PA02

#define LEFT_LINE			PIN_PA02
#define RIGHT_LINE          PIN_PA08
#define LINE_LED			PIN_PA17

#define RIGHT_ENC		    PIN_PA15
#define LEFT_ENC			PIN_PA16

#define SPI_MISO			PIN_PA22
#define SPI_MOSI			PIN_PA25
#define SPI_SCK				PIN_PA23
#define SPI_SS				PIN_PA24

#define LED_DATAIN           PIN_PA27


#endif /* PINOUT_H_ */