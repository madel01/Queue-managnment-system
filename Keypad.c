/*
 * Keypad.c
 *
 * Created: 03/10/2020 12:50:53 م
 *  Author: mohamed
 */ 

#include "DIO.h"
#include <avr/delay.h>
#define F_CPU 1000000UL
char port[] = "A";

int KPD_au8SwitchVal[4][4] =
{
	{ 0x01,0x02,0x03,0x0D },
	{ 0x06,0x05,0x04,0x0E },
	{ 0x07,0x08,0x09,0x0F },
	{ 0x0A,0x00,0x0B,0x0C }
};

int KPD_GetPressedKey(void)
{

	int LOC_Column;

	int LOC_Row;

	/* Initialize the switch status to NOT Pressed                                                                     */
	int LOC_Retrun = 0;
	
	int state = 0b11110000;
	int highHalfstate = 0b01110000;
	
	
	portDataDir(port,state);
	setport(port,255);
	
	
	for(LOC_Column = 0;LOC_Column<4;LOC_Column++){
		
		state = highHalfstate;
		setport(port,state);
		int lowHalfstate = 0b00001000;
		
		for(LOC_Row = 4;LOC_Row<8;LOC_Row++){
			
			if((portRead("A") & lowHalfstate) == 0 ){
				LOC_Retrun = KPD_au8SwitchVal[LOC_Row-4][LOC_Column];
			}
			
			if ((portRead("A") & lowHalfstate) == 0) ;
			_delay_ms(10);
			
			lowHalfstate = lowHalfstate >> 1;
		}
		
		highHalfstate = (highHalfstate >> 1) ^ 0b10001000;
	}
	
	return LOC_Retrun;
}