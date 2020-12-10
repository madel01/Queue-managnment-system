/*
 * QueueManagmentSystem.c
 *
 * Created: 03/10/2020 12:47:35 م
 * Author : mohamed
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include <stdlib.h>
#include "DIO.h"
#include "LCD.h"
#include "Keypad.h"
#define F_CPU 1000000UL

typedef struct node {
	int a;
	int service;
	struct node *newnode;
}node;

void insert(node **head, node **tail,int x,int service);
node erase(node **head,node **tail);
int isempty(node *head);
void printlcd(LCD x,int n);
int x=1;

int main(void)
{
	node *headptr=NULL;
	node *tailptr=NULL;
	
	pinDataDir("D7",0);
	
	LCD LCDportD = LCD_init4("D2","D1","D0","d3","d4","d5","d6");
	function_set(LCDportD,0,1,0);
	disply(LCDportD,1,1,0);
	clear(LCDportD);
	entry_mode(LCDportD,1,0);
	
	LCD LCDportB = LCD_init4("B5","B6","B7","B4","B3","B2","B1");
	function_set(LCDportB,0,1,0);
	disply(LCDportB,1,1,0);
	clear(LCDportB);
	entry_mode(LCDportB,1,0);
	
	
	///////////////////////////
	char string[] = "choose service";
	for(int i=0;string[i] != '\0';i++){
		write(LCDportB,string[i]);
	}
	
	postion(LCDportB,64);
	
	char string1[] = "from 1~9 :-";
	for(int i=0;string1[i] != '\0';i++){
		write(LCDportB,string1[i]);
	}
	//////////////////////////
	
	write(LCDportD,0+48);
	
    while (1) 
    {
		int button = KPD_GetPressedKey();
		
		if(button>0 && button<=9){
		   insert(&headptr,&tailptr,x++,button);
		}
		
		if(pinRead("D7") && !isempty(headptr)){
		   node num = erase(&headptr,&tailptr);
		   clear(LCDportD);
		   printlcd(LCDportD,num.a);
		   postion(LCDportD,64);
		   printlcd(LCDportD,num.service);
		}
		
		
		
	   }
		
    }
	



void insert(node **head, node **tail,int x,int service){
	node *newptr;
	newptr = malloc(sizeof(node));
	
	if(newptr != NULL){
		newptr->a = x;
		newptr->service = service;
		newptr->newnode = NULL;
		if(*head == NULL){
			*head = newptr;
			*tail = newptr;
		}
		else{
			(*tail)->newnode = newptr;
			*tail = newptr;
		}
	}
}

node erase(node **head ,node **tail){
	node *curptr,servedNode;
	//int x;
	
	//x = (*head)->a;
	/*clear(LCDnum);
	printlcd(LCDnum,(*head)->a);
	postion(LCDnum,41);
	printlcd(LCDnum,(*head)->service);*/
	
	curptr = *head;
	servedNode = *curptr;
	*head = (*head)->newnode;
	if(*head==NULL)
	*tail=NULL;
	
	free(curptr);
	return servedNode;
}

int isempty(node *head){
	return head == NULL;
}

void printlcd(LCD x,int n){
	int d=10;
	while(n/d){
		d*=10;
	}
	
	for(d/=10 ; d ; n%=d,d/=10){
		write(x,(char)(n/d)+48);
	}
	
}

