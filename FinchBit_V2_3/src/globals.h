/*
 * globals.h
 *
 * Created: 9/23/2018 11:33:22 AM
 *  Author: raghu
 */ 
#include <asf.h>


uint16_t left_encoder_ticks  = 0;
uint16_t right_encoder_ticks = 0;

#define SPI_DATA_LENGTH 20

bool spi_reset_1 = false;
volatile uint8_t sensor_outputs[20];
volatile uint8_t transmit_value[SPI_DATA_LENGTH];
volatile uint8_t temp_receive[SPI_DATA_LENGTH];
volatile uint8_t received_value[SPI_DATA_LENGTH];
volatile bool transfer_complete_spi_slave = false;

//Serial timeout global variables
volatile uint8_t serial_timeout_count = 0;
volatile bool	 serial_timeout = false;
volatile bool	 transcation_start = false; 

volatile bool	 transferDone = false;

volatile uint8_t DMASourceRegister[NOLEDS*NoBytesLED+2*STARTZEROS];