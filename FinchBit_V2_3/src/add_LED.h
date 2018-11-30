/*
 * addLED.h
 *
 * Created: 9/20/2018 12:55:40 PM
 *  Author: raghu
 */ 


#ifndef ADDLED_H_
#define ADDLED_H_

#define CONF_MASTER_MUX_SETTING SPI_SIGNAL_MUX_SETTING_E
#define CONF_MASTER_PINMUX_PAD0 PINMUX_UNUSED
#define CONF_MASTER_PINMUX_PAD1 PINMUX_UNUSED
#define CONF_MASTER_PINMUX_PAD2 PINMUX_PA08D_SERCOM0_PAD2
#define CONF_MASTER_PINMUX_PAD3 PINMUX_UNUSED
#define CONF_MASTER_SPI_MODULE  SERCOM0


#define NOLEDS     3

#define NoBytesLED 12
#define STARTZEROS 12*5

#define SPIBAUDRATE 2500000

void RGBPI55Init();
struct dma_resource example_resource;
extern volatile bool transferDone;
extern volatile uint8_t DMASourceRegister[NOLEDS*NoBytesLED+2*STARTZEROS]; 

#endif /* ADDLED_H_ */