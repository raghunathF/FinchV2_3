/*
 * sensorsControl.c
 *
 * Created: 10/8/2018 4:21:24 PM
 *  Author: raghu
 */ 
#include<asf.h>
#include "sensorsControl.h"
#include "ultrasound.h"

void readSensors()
{	
	uint16_t temp =0;
	//readLight();
	temp = getUltrasoundDistance();
	sensor_outputs[0] = (temp & 0xFF00)>>8;
	sensor_outputs[1] = temp & 0x00FF;
}