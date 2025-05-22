#include<avr/io.h>
#include<util/delay.h>
#include<stdio.h>
#include<stdlib.h>

int cnt=3;


void se7en_segment(int value){
	switch (value) {
	case 0:
		PORTA=0b01111110;
		break;
	case 1:
		PORTA=0b00001100;
		break;
	case 2:
		PORTA=0b10110110;
		break;
	case 3:
		PORTA=0b10011110;
		break;
	case 4:
		PORTA=0b11001100;
		break;
	case 5:
		PORTA=0b11011010;
		break;
	case 6:
		PORTA=0b11111000;
		break;
	case 7:
		PORTA=0b00001110;
		break;
	}
}

void leds(int value){
	switch (value){
	case 0:
		PORTC=0b01000000;
		break;
	case 1:
		PORTC=0b01000001;
		break;
	case 2:
		PORTC=0b01000010;
		break;
	case 3:
		PORTC=0b01000011;
		break;
	case 4:
		PORTC=0b01000100;
		break;
	case 5:
		PORTC=0b01000101;
		break;
	case 6:
		PORTC=0b01000110;
		break;
	case 7:
		PORTC=0b01000111;
		break;
	}
}

void buzz(){

	PORTC|=(1<<5);
	_delay_ms(500);
	PORTC&=~(1<<5);
	_delay_ms(200);

	/*PORTC|=(1<<5);
	_delay_ms(500);
	PORTC&=~(1<<5);
	_delay_ms(200);
	PORTC|=(1<<5);
	_delay_ms(500);
	PORTC&=~(1<<5);
	_delay_ms(200);

	 */
}

int main(void){
	int num=0;
	DDRD&=~(1<<2);
	DDRD&=~(1<<3);
	DDRD&=~(1<<4);
	DDRD&=~(1<<5);
	DDRC|=(1<<6);
	PORTC|=(1<<6);
	DDRC|=(1<<0);
	DDRC|=(1<<1);
	DDRC|=(1<<2);
	DDRC|=(1<<5);
	DDRA = 0xFE;
	//se7en_segment(num);
	PORTA|=0b01111110;
	int pause=1;


	while(1){
		if(!(PIND &(1<<2)) &&pause==1){
			_delay_ms(30);
			if(!(PIND &(1<<2))){
				if(num<7){
					num++;
					se7en_segment(num);
					leds(num);
				}
				else{
					while(cnt--){
						buzz();
					}
					cnt=3;
				}

			}
			while(!(PIND &(1<<2))){}
		}
		if(!(PIND &(1<<3))&&pause==1){
			_delay_ms(30);
			if(!(PIND &(1<<3))){
				if(num>0){
					num--;
					se7en_segment(num);
					leds(num);
				}
				else{
					while(cnt--){
						buzz();
					}
					cnt=3;
				}

			}
			while(!(PIND &(1<<3))){}
		}
		if(!(PIND &(1<<4))){
			_delay_ms(30);
			if(!(PIND &(1<<4))){
				pause^=1;


			}while(!(PIND &(1<<4))){}
		}

		if(!(PIND &(1<<5))){
			_delay_ms(30);
			if(!(PIND &(1<<5))){
				while(cnt--){
					leds(7);
					_delay_ms(400);
					leds(0);
					_delay_ms(700);
				}
				num=0;
				se7en_segment(0);
			}while(!(PIND &(1<<5))){}
		}


	}

}
