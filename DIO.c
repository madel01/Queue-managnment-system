/*
 * DIO.c
 *
 * Created: 03/10/2020 12:50:14 م
 *  Author: mohamed
 */ 

int *portareg = (int*)0x3B;
int *portbreg = (int*)0x38;
int *portcreg = (int*)0x35;
int *portdreg = (int*)0x32;

int *dataareg = (int*)0x3A;
int *databreg = (int*)0x37;
int *datacreg = (int*)0x34;
int *datadreg = (int*)0x31;

int *pinareg = (int*)0x39;
int *pinbreg = (int*)0x36;
int *pincreg = (int*)0x33;
int *pindreg = (int*)0x30;

void setbit (int *port , int pin , int s){
	*port =   s ? (*port | (1<<pin)) : (*port & ~(1<<pin)) ;
}

int getbit (int *port , int pin ){
	return (*port & (1<<pin)) ? 1 : 0 ;
}

void setpin(char pin[],int state){
	if((pin[0]>='a' && pin[0]<='d') || (pin[0]>='A' && pin[0]<='D')){
		if(pin[1]>='0' && pin[1] <= '7'){
			if(pin[0]=='a' || pin[0]=='A') setbit(portareg,pin[1]-'0',state);
			else if(pin[0]=='b' || pin[0]=='B') setbit(portbreg,pin[1]-'0',state);
			else if(pin[0]=='c' || pin[0]=='C') setbit(portcreg,pin[1]-'0',state);
			else setbit(portdreg,pin[1]-'0',state);
		}
	}
}

void pinDataDir(char pin[],int dir){
	if((pin[0]>='a' && pin[0]<='d') || (pin[0]>='A' && pin[0]<='D')){
		if(pin[1]>='0' && pin[1] <= '7'){
			if(pin[0]=='a' || pin[0]=='A') setbit(dataareg,pin[1]-'0',dir);
			else if(pin[0]=='b' || pin[0]=='B') setbit(databreg,pin[1]-'0',dir);
			else if(pin[0]=='c' || pin[0]=='C') setbit(datacreg,pin[1]-'0',dir);
			else setbit(datadreg,pin[1]-'0',dir);
		}
	}
}

int pinRead(char pin[]){
	int pinput;
	
	if((pin[0]>='a' && pin[0]<='d') || (pin[0]>='A' && pin[0]<='D')){
		if(pin[1]>='0' && pin[1] <= '7'){
			if(pin[0]=='a' || pin[0]=='A') pinput = getbit(pinareg,pin[1]-'0');
			else if(pin[0]=='b' || pin[0]=='B') pinput = getbit(pinbreg,pin[1]-'0');
			else if(pin[0]=='c' || pin[0]=='C') pinput = getbit(pincreg,pin[1]-'0');
			else pinput = getbit(pindreg,pin[1]-'0');
		}
	}
	
	return pinput;
}

void setport (char port[],int state){
	if((port[0]>='a' && port[0]<='d') || (port[0]>='A' && port[0]<='D')){
		if(port[0]=='a' || port[0]=='A') *portareg = state;
		else if(port[0]=='b' || port[0]=='B') *portbreg = state;
		else if(port[0]=='c' || port[0]=='C') *portcreg = state;
		else *portdreg = state;
	}
}

void portDataDir (char port[],int dir){
	if((port[0]>='a' && port[0]<='d') || (port[0]>='A' && port[0]<='D')){
		if(port[0]=='a' || port[0]=='A') *dataareg = dir;
		else if(port[0]=='b' || port[0]=='B') *databreg = dir;
		else if(port[0]=='c' || port[0]=='C') *datacreg = dir;
		else *datadreg = dir;
	}
	
}

int portRead(char port[]){
	int pinput;
	
	if((port[0]>='a' && port[0]<='d') || (port[0]>='A' && port[0]<='D')){
		if(port[0]=='a' || port[0]=='A') pinput = *pinareg;
		else if(port[0]=='b' || port[0]=='B') pinput = *pinbreg;
		else if(port[0]=='c' || port[0]=='C') pinput = *pincreg;
		else pinput = *pindreg;
	}
	
	return pinput;
	
}