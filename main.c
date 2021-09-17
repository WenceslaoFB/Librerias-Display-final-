/*
 * Librerias_display_fin.c
 *
 * Created: 6/9/2021 10:56:07
 * Author : Admin
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "TWI_display.h"

uint8_t texto[]={'Q','U','E',' ','O','N','D','A'};

//Definiciones


//Prototipos de Funciones
void initPorts();
void initTimer();


//Variables Globales
volatile uint8_t flagTwi=0;
volatile uint8_t delay=10;
uint8_t tarea=0;

ISR(TWI_vect){
	flagTwi=1;
	twiInterrupt();
}

void initPorts(){
	//Configuro PIN del LED como salida (PB7 Arduino Mega2560)
	DDRB = (1 << PB7);
	
}

void initTimer(){
	TCCR1A=0x00;// modo CTC(clear timer on compare) del timer 1
	TCCR1B=0x0C;// modo CTC(clear timer on compare) del timer 1 y preescalador = 256
	TIFR1=TIFR1;//borro lo q tenga OCF1A (Output Compare A Match Flag) (para bajar la bandera hay q escribirle un 1 en ese bit)
	TIMSK1=(1<<OCIE1A); //HABILITO INTERRUPCION (OUTPUT COMPARE "A" MATCH INTERRUPT ENABLE)
	//PARA ESCRIBIR EN UN REGISTRO DE 16 BIT PRIMERO DEBO ESCRIBIR EL BYTE ALTO Y DESPUES EL BYTE BAJO
	OCR1AH=0x02;
	OCR1AL=0x71;
	//LE ASIGNE AL REGISTRO OCR1A DE 16 BIT EL VALOR 625
}

ISR(TIMER1_COMPA_vect){
	delay--;
	if(!delay)
	delay=10;
}

int main(void)
{
	cli();
	initPorts();
	initTimer();
	sei();
	_delay_ms(1000);
	flagTwi=1;
	while (1)
	{
		if(flagTwi){
			flagTwi=0;
			switch(tarea){
				case 0:
				if(DefaultInitDisplay_TWI())
				tarea++;
				break;
				case 1:
				if(cleanAllDisplay())
				tarea++;
				break;
				case 2:
				if(WriteDisplay(&texto[0],0xB0,10))
				tarea++;
				break;
			}
		}
	}
}