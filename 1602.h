sbit rs=P2^6;
sbit rw=P2^5;
sbit e=P2^7;

void delayms(unsigned int ms)
{
  unsigned int i,j;
	for(j=0;j<ms;j++)
 	 for(i=0;i<300;i++);
}

bit busy_check()
{
  bit stat;
	rs=0;
	rw=1;
	e=0;
	delayms(1);
	e=1;
	delayms(1);
	stat=P0&0x80;
	e=0;
	delayms(1);
	return stat;
}

void lcdcom(unsigned char com)   
{
  while(busy_check());
		rs=0;
    rw=0;
	  e=0;
	  delayms(1);
	  P0=com;
	  e=1;
	  delayms(1);
	  e=0;
	  delayms(1);	
}

void lcddat(unsigned char dat)   
{
  while(busy_check());
		rs=1;
    rw=0;
	  e=0;
	  delayms(1);
	  P0=dat;
	  e=1;
	  delayms(1);
	  e=0;	
	  delayms(1);
}

void lcdinit(char string[])
{ 	unsigned int i;
    lcdcom(0x38);    //打开，5*8,8位数据
	lcdcom(0x0c);
	lcdcom(0x06);
	lcddat(0x01);    //清屏
	lcdcom(0x80); //第一行
	for(i=0;i<strlen(string);i++)
	{
	lcddat(string[i]);
	}	
}












