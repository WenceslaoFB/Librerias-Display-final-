/*
 * TWI_display.c
 *
 * Created: 6/9/2021 11:33:44
 *  Author: Admin
 */ 
#include "font1.h"
#include "TWI_display.h"

static uint8_t twi_Status=0;
static uint8_t comando=0;


void twiInterrupt(){
	twi_Status=TWSR&0xF8;
}

uint8_t WriteDisplay(uint8_t *string, uint8_t page,uint8_t cantLetras){
	static uint8_t write=0,k=0,j=0;
	uint8_t caracter=0;
	
	switch(twi_Status){
		case 0:
		twi_Status=1;
		InitDisplay_TWI(ATMEGA2560);
		break;
		case TWI_STARTED:
		twi_Status=1;
		SlaveAddrsDisplay_TWI(ATMEGA2560);
		break;
		case SLA_W_SENT: case DATA_RECEIVED:
		twi_Status=1;
		write=1;
		break;
	}

	if(write){
		write=0;
		switch(comando){
			case 0:
			DataDisplay_TWI(ATMEGA2560,0x80);
			comando++;
			break;
			case 1:
			DataDisplay_TWI(ATMEGA2560,page);
			comando++;
			break;
			case 2:
			DataDisplay_TWI(ATMEGA2560,0x40);
			comando++;
			break;
			case 3:
			if(k<cantLetras){
				caracter=pgm_read_byte_near(&ROMCHAR[*(string+k)*8+j]);
				DataDisplay_TWI(ATMEGA2560,caracter);
				j++;
				if(j==8){
					k++;
					j=0;
				}
			}
			else{
				comando=0;
				StopDisplay_TWI(ATMEGA2560);
				twi_Status=0;
				return 1;
			}
			break;
		}
	}
	return 0;
}

uint8_t DefaultInitDisplay_TWI(){
	switch(twi_Status){
		case 0:
		twi_Status=1;
		InitDisplay_TWI(ATMEGA2560);
		break;
		case TWI_STARTED:
		twi_Status=1;
		SlaveAddrsDisplay_TWI(ATMEGA2560);
		break;
		case SLA_W_SENT: case DATA_RECEIVED:
		twi_Status=1;
		SettingsDisplay();
		if(comando==LAST_COMAND_RECEIVED){
			StopDisplay_TWI(ATMEGA2560);
			comando=0;
			twi_Status=0;
			return 1;
		}
		break;
	}
	return 0;
}
void SettingsDisplay(){
	switch(comando){
		case 0:
		DataDisplay_TWI(ATMEGA2560,CTRL_BYTE_COMANDO);
		comando++;
		break;
		case 1:
		DataDisplay_TWI(ATMEGA2560,DISPLAY_OFF);
		comando++;
		break;
		case 2:
		DataDisplay_TWI(ATMEGA2560,CLK_DIVR_OSC_FREQ);
		comando++;
		break;
		case 3:
		DataDisplay_TWI(ATMEGA2560,0x80);
		comando++;
		break;
		case 4:
		DataDisplay_TWI(ATMEGA2560,MPLX_NUMBER);
		comando++;
		break;
		case 5:
		DataDisplay_TWI(ATMEGA2560,0x3F);
		comando++;
		break;
		case 6:
		DataDisplay_TWI(ATMEGA2560,DISPLAY_OFFSET);
		comando++;
		break;
		case 7:
		DataDisplay_TWI(ATMEGA2560,0);
		comando++;
		break;
		case 8:
		DataDisplay_TWI(ATMEGA2560,RAM_STARTLINE_REG);
		comando++;
		break;
		case 9:
		DataDisplay_TWI(ATMEGA2560,CHARGE_PUMP);
		comando++;
		break;
		case 10:
		DataDisplay_TWI(ATMEGA2560,0x14);
		comando++;
		break;
		case 11:
		DataDisplay_TWI(ATMEGA2560,SEGMENT_REMAP);
		comando++;
		break;
		case 12:
		DataDisplay_TWI(ATMEGA2560,COM_OUT_SCAN_DIR);
		comando++;
		break;
		case 13:
		DataDisplay_TWI(ATMEGA2560,COM_PINS_CONFIG);
		comando++;
		break;
		case 14:
		DataDisplay_TWI(ATMEGA2560,0x12);
		comando++;
		break;
		case 15:
		DataDisplay_TWI(ATMEGA2560,CONTRAST);
		comando++;
		break;
		case 16:
		DataDisplay_TWI(ATMEGA2560,0x9F);
		comando++;
		break;
		case 17:
		DataDisplay_TWI(ATMEGA2560,MEMORY_ADRESS_MODE);
		comando++;
		break;
		case 18:
		DataDisplay_TWI(ATMEGA2560,0x02);//Memory Addressing Mode (Horizontal=0 , Vertical=1 , Page=2)
		comando++;
		break;
		case 19:
		DataDisplay_TWI(ATMEGA2560,DISABLE_SCROLL);
		comando++;
		break;
		case 20:
		DataDisplay_TWI(ATMEGA2560,PRE_CHARGE_PERIOD);
		comando++;
		break;
		case 21:
		DataDisplay_TWI(ATMEGA2560,0x22);
		comando++;
		break;
		case 22:
		DataDisplay_TWI(ATMEGA2560,VCOMH_DESELECT_LEVEL);
		comando++;
		break;
		case 23:
		DataDisplay_TWI(ATMEGA2560,0x40);
		comando++;
		break;
		case 24:
		DataDisplay_TWI(ATMEGA2560,RESUME_TO_RAM);
		comando++;
		break;
		case 25:
		DataDisplay_TWI(ATMEGA2560,DISPLAY_INVERSE_MODE);
		comando++;
		break;
		case 26:
		DataDisplay_TWI(ATMEGA2560,DISPLAY_ON);
		comando++;
		break;
		case 27:
		comando=LAST_COMAND_RECEIVED;
		break;
	}
}



uint8_t cleanPage(uint8_t page){
	static uint8_t clean=0,i=0;
	switch(twi_Status){
		case 0:
		twi_Status=1;
		InitDisplay_TWI(ATMEGA2560);
		break;
		case TWI_STARTED:
		twi_Status=1;
		SlaveAddrsDisplay_TWI(ATMEGA2560);
		break;
		case SLA_W_SENT: case DATA_RECEIVED:
		twi_Status=1;
		clean=1;
		break;
	}
	if(clean){
		clean=0;
		switch(comando){
			case 0:
			DataDisplay_TWI(ATMEGA2560,0x80);
			comando++;
			break;
			case 1:
			DataDisplay_TWI(ATMEGA2560,page);
			comando++;
			break;
			case 2:
			DataDisplay_TWI(ATMEGA2560,0x40);
			comando++;
			break;
			case 3:
			if(i<128){
				DataDisplay_TWI(ATMEGA2560,0x00);
				i++;
			}
			else{
				i=0;
				StopDisplay_TWI(ATMEGA2560);
				comando=0;
				twi_Status=0;
				return 1;
			}
			break;
		}
	}
	return 0;
}

uint8_t cleanAllDisplay(){
	static uint8_t page=0;
	switch(page){
		case 0:
		if(cleanPage(0xB0))
		page++;
		break;
		case 1:
		if(cleanPage(0xB1))
		page++;
		break;
		case 2:
		if(cleanPage(0xB2))
		page++;
		break;
		case 3:
		if(cleanPage(0xB3))
		page++;
		break;
		case 4:
		if(cleanPage(0xB4))
		page++;
		break;
		case 5:
		if(cleanPage(0xB5))
		page++;
		break;
		case 6:
		if(cleanPage(0xB6))
		page++;
		break;
		case 7:
		if(cleanPage(0xB7)){
			page=0;
			return 1;
		}
		break;
	}
	return 0;
}



uint8_t InitDisplay_TWI(uint8_t micro){
	if	(micro==ATMEGA2560){
		TWBR=((16000000UL/SCL_CLOCK)-16)/2;			//Factor de division del bitrate generator = 32
		TWSR&=~((1<<TWPS0)|(1<<TWPS1));						//TWI Prescaler = 1
		TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN)|(1<<TWIE);
		return 1;
	}
	return 0;
}

uint8_t SlaveAddrsDisplay_TWI(uint8_t micro){
	if(micro==ATMEGA2560){
		TWDR=SLAVE_WRITE;
		TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWIE);
		return 1;
	}
	return 0;
}

uint8_t DataDisplay_TWI(uint8_t micro,uint8_t data){
	if(micro==ATMEGA2560){
		TWDR=data;
		TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWIE);
		return 1;
	}
	return 0;
}

uint8_t StopDisplay_TWI(uint8_t micro){
	if(micro==ATMEGA2560){
		TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
		return 1;
	}
	return 0;
}
