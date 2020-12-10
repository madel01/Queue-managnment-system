/*
 * DIO.h
 *
 * Created: 03/10/2020 12:49:21 م
 *  Author: mohamed
 */ 


#ifndef DIO_H_
#define DIO_H_

void setpin(char pin[],int state);
void pinDataDir(char pin[],int dir);
int  pinRead(char pin[]);
int  portRead(char port[]);
void setport (char port[],int state);
void portDataDir (char port[],int dir);



#endif /* DIO_H_ */