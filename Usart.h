unsigned char ttldat[3];
 void UsartInit()
{
	SCON=0X50;			//设置为工作方式1
	TMOD=0X21;			//设置计数器工作方式2
	PCON=0X80;			//波特率加倍

	TH1=0XF3;				//计数器初始值设置，注意波特率是4800的
	TL1=0XF3;

	ES=1;						//打开接收中断
	EA=1;						//打开总中断
	TR1=1;					//打开计数器
}


 void SendByte(unsigned char dat)
 {
   TI=0;	
   SBUF=dat+0x30;
   while(!TI);			 //等待发送数据完成
   TI=0;
 }
  void SendChar(unsigned char dat)
 {
	TI=0;	
	SBUF=dat;
	while(!TI);			 //等待发送数据完成
	TI=0;
 }
 void SendString(unsigned char dat[])
 {		
   unsigned int i;
	 unsigned int len;
	 len=strlen(dat);
   for(i=0;i<len;i++)
   {	   
   SendChar(dat[i]);
   }
}
void SendData()
{	
    unsigned int i;
    unsigned char a[]="距离:";	
	   
	  // SendString(a);
	  SendChar('D');
	   for(i=0;i<3;i++)
	   {   if(i==1)
	   		 SendChar('.');
	     SendByte(ttldat[i]);
    	}
		// SendChar('M');
	    SendChar('\r');
	    SendChar('\n');
	
 }		

			