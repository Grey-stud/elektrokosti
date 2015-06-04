/*
 * elektrokosti.c
 *
 * Created: 28.05.2015 16:56:17
 *  Author: Sergey
 */ 

#define F_CPU 128000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#include <avr/sleep.h>
#include <avr/power.h>
#include <util/delay.h>

#define led1 PB3
#define led2 PB1
#define led3 PB6
#define led4 PD6
#define led5 PD2
#define led6 PD5
#define led7 PD4

#define key PIND3


unsigned int i,j;// asm("r16");
unsigned char k;


void led_on()
{
	PORTD&=~((1<<led4)|(1<<led5)|(1<<led6)|(1<<led7));
	PORTB&=~((1<<led1)|(1<<led2)|(1<<led3));	
}

void led_off()
{
	PORTD|=((1<<led4)|(1<<led5)|(1<<led6)|(1<<led7));
	PORTB|=((1<<led1)|(1<<led2)|(1<<led3));	
}

void deg_to_led(unsigned char deg)
{
	switch(deg)
	{
		case 1:
		{
			
			PORTD=0b00111100;
			PORTB=0b01001010;
			break;
		}
		case 2:
		{
			PORTD=0b01111000;
			PORTB=0b00001010;
			break;
		}
		case 3:
		{
			PORTD=0b00111000;
			PORTB=0b00001010;
			break;
		}
		case 4:
		{
			PORTD=0b01101000;
			PORTB=0b00000010;
			break;
		}
		case 5:
		{
			PORTD=0b00101000;
			PORTB=0b00000010;
			break;
		}
		
		case 6:
		{
			PORTD=0b01001000;
			PORTB=0b00000000;
			break;
		}
	}
	
	
}

void show_led(unsigned char i)
{
	switch(i)
	{
		case 1: 
		{
			led_off();
			PORTB&=~(1<<led1);
			break;
		}
		case 2:
		{
			led_off();
			PORTB&=~(1<<led2);
			break;
		}
		case 3:
		{
			led_off();
			PORTB&=~(1<<led3);
			break;
		}
		case 4:
		{
			led_off();
			PORTD&=~(1<<led7);
			break;
		}
		case 5:
		{
			led_off();
			PORTD&=~(1<<led6);
			break;			
		}
		
		case 6:
		{
			led_off();
			PORTD&=~(1<<led5);
			break;			
		}
	}
	
	
}

//ISR(em)

ISR(INT1_vect)
{
GIMSK&=~(1<<INT1);
//cli();	
//GIMSK=0b00000000;
//MCUCR|=(1<<ISC10);
//		PORTD=0b00001000;
//		PORTB=0b00000000;
//		_delay_ms (1);
//show_led(k);
}



int main(void)
{
cli();

	PORTD=0b01111100;
//	PORTD=0b00000100;
	 DDRD=0b01110100;
	PORTB=0b01001010;
//	PORTB=0b00000000;
	 DDRB=0b01001010;


		led_off();
		PORTD&=~(1<<led4);
		_delay_ms (200);
		led_off();
		_delay_ms (200);
		led_off();
		PORTD&=~(1<<led4);
		_delay_ms (200);
		led_off();
		_delay_ms (200);
		led_off();
		PORTD&=~(1<<led4);
		_delay_ms (200);
		led_off();

//deg_to_led(5);
//MCUCR|=(1<<ISC10);
GIMSK|=(1<<INT1);
//	GIMSK=0b10000000;

//	MCUCR=0b00000010;
//	PCMSK=0b00001000;	
	

	
set_sleep_mode(SLEEP_MODE_PWR_DOWN);
//power_all_disable();	

	sei();
    sleep_mode();		
    while(1)
    {
		while (!(PIND&(1<<key)))
		{
			i++;
			j++;
			if(j>360)
			{
				j=0;
				k++;
				show_led((k%6)+1);
			}
		}  
		deg_to_led((i%6)+1);
	    _delay_ms (3000);
		led_off();
		GIMSK|=(1<<INT1);
		sleep_mode();
    }
}