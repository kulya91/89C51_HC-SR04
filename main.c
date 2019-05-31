#include<reg51.h>
#include<string.h>
#include"1602.h"
#include"Usart.h"
sbit Trig = P2^1;
sbit Echo = P2^0;

typedef unsigned int u16;
typedef unsigned char u8;

 u8 flag;
 u16 time;
 u16 S;
 int limi=0,fenmi=0,mi=0;
 
void count()
{
	time=TH0*256+TL0;
	 TH0=0;
	 TL0=0;
	
	 S=(time*1.7)/100;
	if((S>=700)||flag==1)
	 {	 
	  flag=0;
	
	limi=9;
		 fenmi=9;
		 mi=9 ;
	 }
	 else
	 {
		limi=S%10;
	fenmi=S/10%10;
	mi=S/100;
	 }
	 if((limi>=0&&limi<=9)&&(fenmi>=0&&fenmi<=9)&&(mi>=0&&mi<=8))
	 {
	 ttldat[2]=limi;
	  ttldat[1]=fenmi;
	  ttldat[0]=mi;
		}
}

void lcddisplay()
{
	lcdcom(0xc5);
	
	lcddat(ttldat[0]+0x30);
	lcddat('.');
	lcddat(ttldat[1]+0x30);
	lcddat(ttldat[2]+0x30);
	lcddat('M');
	
}


void main(void)
{
    lcdinit("distance:");	
	UsartInit();
	Trig=0;	   
    TH0=0;
    TL0=0;       
	ET0=1;            
	while(1)
	{
		Trig=1;
		delayms(1);
		 Trig=0;
		while(!Echo);		//当RX为零时等待
		TR0=1;			    //开启计数
		while(Echo);			//当RX为1计数并等待
		TR0=0;				//关闭计数
		count();
		lcddisplay();
		delayms(100);
		TI=1;
	}
			
}

	void zd0() interrupt 1 
{
	flag=1;
	
}

  void Usart() interrupt 4
{  		
		SendData();
	
}