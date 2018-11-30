/*
 * add_LED_control.c
 *
 * Created: 9/20/2018 4:55:06 PM
 *  Author: raghu
 */ 
#include <asf.h>
#include "add_LED.h"
#include "add_LED_control.h"

#define SIZE_LED_VALUES 48

#define NO_LEDS 3
#define COLORS  3 

#define HIGH_0	1
#define LOW_0	1

#define HIGH_1	1
#define LOW_1	1

static	uint8_t		led_delays[3][48];

#define TWOBITSPIVALUES {0x88,0x8E,0xE8,0xEE}
const	uint8_t SPIDataConertConsArray[] = TWOBITSPIVALUES;


static uint8_t* convertColorSPIData(colorInfo* colorData )
{
	volatile static uint8_t SPIData[NoBytesLED];
	volatile uint8_t i =0;
	uint8_t countSPIData = 0;
	volatile uint8_t temp =0;
	volatile uint8_t twoBitValue = 0;
	for(i=0;i<4;i++)
	{
		twoBitValue = (colorData->GBrightness & (0xC0>>i*2))>>(6-2*i);
		SPIData[countSPIData] = SPIDataConertConsArray[twoBitValue];
		countSPIData++;
	}
	for(i=0;i<4;i++)
	{
		//temp = (0x30>>(i*2));
		twoBitValue = (colorData->RBrightness & (0xC0>>i*2))>>(6-2*i);
		SPIData[countSPIData] = SPIDataConertConsArray[twoBitValue];
		countSPIData++;
	}
	for(i=0;i<4;i++)
	{
		twoBitValue = (colorData->BBrightness & (0xC0>>i*2))>>(6-2*i);
		SPIData[countSPIData] = SPIDataConertConsArray[twoBitValue];
		countSPIData++;
	}
	return SPIData;
};

void RGBPI55SetLED(uint8_t LEDNumber , colorInfo color_led )
{
	uint8_t i =0;
	uint16_t startArrayAddress = 0;
	uint8_t* LEDSPIData = NULL;
	startArrayAddress = LEDNumber*NoBytesLED + STARTZEROS ;
	LEDSPIData = convertColorSPIData(&color_led);
	for(i = 0 ; i < NoBytesLED ; i++)
	{
		DMASourceRegister[i+startArrayAddress]   = LEDSPIData[i] ;
	}
	dma_start_transfer_job(&example_resource);
	while(transferDone == false);
	transferDone = false;
}

/*
uint8_t* oneandzero_delays(uint8_t* led_values )
{
	uint8_t i,j = 0;
	bool bool_value = false;
	static uint8_t* delays = NULL;
	delays = malloc(sizeof(uint8_t) * SIZE_LED_VALUES);
	
	for(j=0;j<COLORS;j++)
	{
		for(i=0;i<8;i++)
		{
			bool_value = ((led_values[j] << i) & 0x80) >> 7 ;
			if(bool_value == true)
			{
				delays[i*2 + 16*j]      = HIGH_1;
				delays[i*2 + 1 + 16*j ] = LOW_1;
			}
			else
			{
				delays[i*2 + 16*j]		= HIGH_0;
				delays[i*2+ 1 + 16*j]	= LOW_0 ;
			}
		}
	}
	return delays;
}


//Better structuring for coding so that we can abstract 
void transfer_data(uint8_t* temp , uint8_t i)
{
	uint8_t j = 0;
	for(j=0;j<48;j++)
	{
		led_delays[i][j] = temp[j];
	}
}

void bitbang_data()
{
	send_24bits(&led_delays[0][0]);
	send_reset();
	send_24bits(&led_delays[1][0]);
	send_reset();
	send_24bits(&led_delays[2][0]);
	send_reset();
}

//SPI call to the LED
void control_LED(uint8_t* rgb_ledvalues)
{
	uint8_t i =0;
	uint8_t* led_values = NULL;
	led_values = malloc(sizeof(uint8_t)*3);
	uint8_t* temp = NULL;
	volatile uint8_t test1 = 0;
	volatile uint8_t test2 = 0;
	volatile uint8_t test3 = 0;
	//test1	= rgb_ledvalues[0];
	//test2	= rgb_ledvalues[1];
	//test3	= rgb_ledvalues[2];
	
	for(i=0;i<NO_LEDS;i++)
	{
		led_values[0]   = rgb_ledvalues[i*3+1];
		led_values[1]	= rgb_ledvalues[i*3];
		led_values[2]	= rgb_ledvalues[i*3+2]; 
	    temp            = oneandzero_delays(led_values);
		transfer_data(temp,i);
	}
	bitbang_data();
	
}
*/