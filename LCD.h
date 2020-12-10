/*
 * LCD.h
 *
 * Created: 03/10/2020 12:49:40 م
 *  Author: mohamed
 */ 


#ifndef LCD_H_
#define LCD_H_

typedef struct LCD {
	int  mode; //4bit (0) ,,, 8bit (1)
	char Enable[3];
	char RW[3];
	char RS[3];
	char pins[8][3];
}LCD;

LCD LCD_init8(char Enable[], char RW[], char RS[], char p0[], char p1[], char p2[], char p3[], char p4[], char p5[], char p6[], char p7[]);
LCD LCD_init4(char Enable[], char RW[], char RS[], char p4[], char p5[], char p6[], char p7[]);
void function_set(LCD x,int datalines,int displaylines,int font);
void entry_mode(LCD x,int ID,int SH);
void write(LCD x, char str);
void clear(LCD x);
void disply(LCD x, int display,int cursor,int blink);
void shift(LCD x,int SC,int RL);
void postion(LCD x,int index);



#endif /* LCD_H_ */