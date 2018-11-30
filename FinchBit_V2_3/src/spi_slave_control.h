/*
 * spi_slave_control.h
 *
 * Created: 9/25/2018 1:56:22 PM
 *  Author: raghu
 */ 


#ifndef SPI_SLAVE_CONTROL_H_
#define SPI_SLAVE_CONTROL_H_

extern volatile bool transcation_start;
extern volatile bool serial_timeout;

#define SPI_LENGTH 7

//extern  volatile uint8_t received_value[20];
//extern  volatile uint8_t transmit_value[20];

//extern volatile uint8_t sensor_outputs[20];
//extern volatile bool transcation_start;
//extern volatile bool serial_timeout;
extern volatile uint8_t serial_timeout_count;
extern volatile bool status_battery ;
extern volatile bool init_status_battery ;

void spi_main_loop();

#endif /* SPI_SLAVE_CONTROL_H_ */