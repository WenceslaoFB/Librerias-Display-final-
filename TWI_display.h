/*
 * TWI_display.h
 *
 * Created: 6/9/2021 11:34:07
 *  Author: Admin
 */ 


#ifndef TWI_DISPLAY_H_
#define TWI_DISPLAY_H_

//Definiciones
#define ATMEGA2560	1
#define SCL_CLOCK 100000UL
#define DISPLAY_HEIGHT 64 //display 64pixls x 128 pixls
#define DISPLAY_WIDTH 128 //display 64pixls x 128 pixls
#define TWI_STARTED 0x08
#define TWI_RESTARTED 0x10
#define SLA_W_SENT	0x18
#define DATA_RECEIVED	0x28
#define NACK_RECEIVED 	0x30
#define LAST_COMAND_RECEIVED	0xF0
#define SLAVE_WRITE	(0x3C<<1)
#define SLAVE_READ  (0x3C<<1)|(0x01)

#define CTRL_BYTE_COMANDO 0
#define CTRL_BYTE_DATO 0x40
#define DISPLAY_OFF	0xAE
#define DISPLAY_ON 0xAF
#define CLK_DIVR_OSC_FREQ	0xD5// Display clock divide ratio & Oscillator frequency
#define MPLX_NUMBER	0xA8//Set Multiplex number(activated rows): ( range 16 ~ 64 )
#define DISPLAY_OFFSET	0xD3
#define RAM_STARTLINE_REG	0x40//Set display RAM start line register
#define CHARGE_PUMP	0x8D
#define SEGMENT_REMAP	0xA1 //SEG (columns) normal(0xA0) mode, (inverse=0xA1)
#define	COM_OUT_SCAN_DIR 0xC8 //COM (rows) normal mode(0xC0), (inverse=0xC8)
#define COM_PINS_CONFIG	0xDA//Set COM Pins Hardware config
#define CONTRAST	0x81	//Set Contrast Control
#define	MEMORY_ADRESS_MODE	0x20 //Memory Addressing Mode
#define DISABLE_SCROLL 0x2E
#define PRE_CHARGE_PERIOD	0xD9 //Pre-charge period
#define VCOMH_DESELECT_LEVEL	0xDB
#define	DISPLAY_NORMAL_MODE 0xA6
#define	DISPLAY_INVERSE_MODE 0xA7
#define ENTIRE_DISPLAY_ON 0xA5
#define	RESUME_TO_RAM 0xA4

//Prototipos de Funciones
uint8_t InitDisplay_TWI(uint8_t micro);
uint8_t SlaveAddrsDisplay_TWI(uint8_t micro);
uint8_t DataDisplay_TWI(uint8_t micro,uint8_t data);
uint8_t StopDisplay_TWI(uint8_t micro);
void SettingsDisplay();
uint8_t DefaultInitDisplay_TWI();
uint8_t WriteDisplay(uint8_t *string,uint8_t page,uint8_t cantLetras);
uint8_t cleanAllDisplay();
uint8_t cleanPage(uint8_t page);
void twiInterrupt();

#endif /* TWI_DISPLAY_H_ */