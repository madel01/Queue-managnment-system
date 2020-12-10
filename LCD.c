/*
 * LCD.c
 *
 * Created: 03/10/2020 12:50:31 م
 *  Author: mohamed
 */ 

#include "DIO.h"
#include "string.h"
#include "LCD.h"
#include <avr/delay.h>

LCD LCD_init8(char Enable[], char RW[], char RS[], char p0[], char p1[], char p2[], char p3[], char p4[], char p5[], char p6[], char p7[]){
	
	LCD newLCD ;
	newLCD.mode=1;
	strcpy(newLCD.Enable,Enable);
	strcpy(newLCD.RS,RS);
	strcpy(newLCD.RW,RW);
	strcpy(newLCD.pins[0] ,p0);
	strcpy(newLCD.pins[1] ,p1);
	strcpy(newLCD.pins[2] ,p2);
	strcpy(newLCD.pins[3] ,p3);
	strcpy(newLCD.pins[4] ,p4);
	strcpy(newLCD.pins[5] ,p5);
	strcpy(newLCD.pins[6] ,p6);
	strcpy(newLCD.pins[7] ,p7);
	
	_delay_ms(30); // wait 30ms to rise VDD
	
	//////////////////////////////// set data direction of pins
	pinDataDir(newLCD.Enable,1);
	pinDataDir(newLCD.RW,1);
	pinDataDir(newLCD.RS,1);
	for(int i=0;i<8;i++)
	pinDataDir(newLCD.pins[i],1);
	///////////////////////////////
	
	return newLCD;
	
}

LCD LCD_init4(char Enable[], char RW[], char RS[], char p4[], char p5[], char p6[], char p7[]){
	
	LCD newLCD ;
	newLCD.mode=0;
	strcpy(newLCD.Enable ,Enable);
	strcpy(newLCD.RS ,RS);
	strcpy(newLCD.RW ,RW);
	strcpy(newLCD.pins[4] ,p4);
	strcpy(newLCD.pins[5] ,p5);
	strcpy(newLCD.pins[6] ,p6);
	strcpy(newLCD.pins[7] ,p7);
	
	_delay_ms(30); // wait 30ms to rise VDD
	
	//////////////////////////////// set data direction of pins
	pinDataDir(newLCD.Enable,1);
	pinDataDir(newLCD.RW,1);
	pinDataDir(newLCD.RS,1);
	for(int i=4;i<8;i++)
	pinDataDir(newLCD.pins[i],1);
	///////////////////////////////
	
	return newLCD;
	
}

void function_set(LCD x,int datalines,int displaylines,int font){
	setpin(x.RS,0);
	setpin(x.RW,0);
	
	setpin(x.pins[7],0);
	setpin(x.pins[6],0);
	setpin(x.pins[5],1);
	setpin(x.pins[4],datalines);
	
	if(x.mode){
		setpin(x.pins[3],displaylines);
		setpin(x.pins[2],font);
		setpin(x.pins[1],0);
		setpin(x.pins[0],0);
	}
	
	else{
		setpin(x.Enable,1);
		_delay_ms(1);
		setpin(x.Enable,0);
		
		_delay_us(40);
		
		setpin(x.pins[7],0);
		setpin(x.pins[6],0);
		setpin(x.pins[5],1);
		setpin(x.pins[4],0);
		
		setpin(x.Enable,1);
		_delay_ms(1);
		setpin(x.Enable,0);
		
		_delay_us(40);
		
		setpin(x.pins[7],displaylines);
		setpin(x.pins[6],font);
		setpin(x.pins[5],0);
		setpin(x.pins[4],0);
	}
	
	setpin(x.Enable,1);
	_delay_ms(1);
	setpin(x.Enable,0);
	
	_delay_us(40);
}

void entry_mode(LCD x,int ID,int SH){
	setpin(x.RS,0);
	setpin(x.RW,0);
	
	setpin(x.pins[7],0);
	setpin(x.pins[6],0);
	setpin(x.pins[5],0);
	setpin(x.pins[4],0);
	
	if(x.mode){
		setpin(x.pins[3],0);
		setpin(x.pins[2],1);
		setpin(x.pins[1],ID);
		setpin(x.pins[0],SH);
	}
	
	else{
		setpin(x.Enable,1);
		_delay_ms(1);
		setpin(x.Enable,0);
		
		_delay_us(40);
		
		setpin(x.pins[7],0);
		setpin(x.pins[6],1);
		setpin(x.pins[5],ID);
		setpin(x.pins[4],SH);
	}
	
	setpin(x.Enable,1);
	_delay_ms(1);
	setpin(x.Enable,0);
	
	_delay_us(40);
}

void write(LCD x, char str){
	setpin(x.RS,1);
	setpin(x.RW,0);
	
	int j=7,n=128;
	while(j>=4){
		setpin(x.pins[j],str & n);
		n = (n >> 1);
		j--;
	}
	
	if(x.mode){
		while(j>=0){
			setpin(x.pins[j],str & n);
			n = (n >> 1);
			j--;
		}
	}
	else{
		setpin(x.RS,1);
		setpin(x.RW,0);
		
		setpin(x.Enable,1);
		_delay_ms(1);
		setpin(x.Enable,0);
		
		_delay_us(40);
		
		for(j=7;j>=4;j--){
			setpin(x.pins[j],str & n);
			n = (n >> 1);
		}
	}
	
	setpin(x.RS,1);
	setpin(x.RW,0);
	
	setpin(x.Enable,1);
	_delay_ms(1);
	setpin(x.Enable,0);
	
	_delay_us(40);
	
}

void clear(LCD x){
	setpin(x.RS,0);
	setpin(x.RW,0);
	
	setpin(x.pins[7],0);
	setpin(x.pins[6],0);
	setpin(x.pins[5],0);
	setpin(x.pins[4],0);
	
	if(x.mode){
		setpin(x.pins[3],0);
		setpin(x.pins[2],0);
		setpin(x.pins[1],0);
		setpin(x.pins[0],1);
	}
	
	else{
		setpin(x.Enable,1);
		_delay_ms(1);
		setpin(x.Enable,0);
		
		_delay_ms(2);
		
		setpin(x.pins[7],0);
		setpin(x.pins[6],0);
		setpin(x.pins[5],0);
		setpin(x.pins[4],1);
	}
	
	setpin(x.Enable,1);
	_delay_ms(1);
	setpin(x.Enable,0);
	
	_delay_ms(2);
}

void disply(LCD x, int display,int cursor,int blink){
	setpin(x.RS,0);
	setpin(x.RW,0);
	
	setpin(x.pins[7],0);
	setpin(x.pins[6],0);
	setpin(x.pins[5],0);
	setpin(x.pins[4],0);
	
	if(x.mode){
		setpin(x.pins[3],1);
		setpin(x.pins[2],display);
		setpin(x.pins[1],cursor);
		setpin(x.pins[0],blink);
	}
	
	else{
		setpin(x.Enable,1);
		_delay_ms(1);
		setpin(x.Enable,0);
		
		_delay_us(40);
		
		setpin(x.pins[7],1);
		setpin(x.pins[6],display);
		setpin(x.pins[5],cursor);
		setpin(x.pins[4],blink);
	}
	
	
	setpin(x.Enable,1);
	_delay_ms(1);
	setpin(x.Enable,0);
	
	_delay_us(40);
}

void shift(LCD x,int SC,int RL){
	setpin(x.RS,0);
	setpin(x.RW,0);
	
	setpin(x.pins[7],0);
	setpin(x.pins[6],0);
	setpin(x.pins[5],0);
	setpin(x.pins[4],1);
	
	if(x.mode){
		setpin(x.pins[3],SC);
		setpin(x.pins[2],RL);
		setpin(x.pins[1],0);
		setpin(x.pins[0],0);
	}
	else{
		setpin(x.Enable,1);
		_delay_ms(1);
		setpin(x.Enable,0);
		
		_delay_us(40);
		
		setpin(x.pins[7],SC);
		setpin(x.pins[6],RL);
		setpin(x.pins[5],0);
		setpin(x.pins[4],0);
		
	}
	
	setpin(x.Enable,1);
	_delay_ms(1);
	setpin(x.Enable,0);
	
	_delay_us(40);
}

void postion(LCD x,int index){
	setpin(x.RS,0);
	setpin(x.RW,0);
	
	index += 128;
	
	int j=7,n=128;
	while(j>=4){
		setpin(x.pins[j],index & n);
		n = (n >> 1);
		j--;
	}
	
	if(x.mode){
		while(j>=0){
			setpin(x.pins[j],index & n);
			n = (n >> 1);
			j--;
		}
	}
	else{
		setpin(x.RS,0);
		setpin(x.RW,0);
		
		setpin(x.Enable,1);
		_delay_ms(1);
		setpin(x.Enable,0);
		
		_delay_us(40);
		
		for(j=7;j>=4;j--){
			setpin(x.pins[j],index & n);
			n = (n >> 1);
		}
	}
	
	/*for(int j=0;j<8;j++){
		setpin(x.pins[j],index & 1);
		index = (index >> 1);
	}*/
	
	setpin(x.RS,0);
	setpin(x.RW,0);
	
	setpin(x.Enable,1);
	_delay_ms(1);
	setpin(x.Enable,0);
	
	_delay_us(40);
	
}
