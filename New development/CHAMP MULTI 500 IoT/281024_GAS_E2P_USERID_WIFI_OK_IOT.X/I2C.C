void i2cinit()
{
    SDA1IO=0;
    SCL1IO=0;
    ODCAbits.ODCA15 = 1;     
}
void startBitGen()
{
	SDA1IO = 0;
		
	SDA = 1;
	delayI2C();
	SCL = 1;
	delayI2C();
	SDA = 0;
	delayI2C();		
	SCL = 0;
	delayI2C();
	
	SDA1IO = 0;
	
}
void stopBitGen()
{
	SDA1IO = 0;
	
	SDA = 0;
	delayI2C();	
	SCL = 1;
	delayI2C();
	SDA = 1;
	delayI2C();
	
	SDA1IO = 0;
}

void I2C_Write1(unsigned int addr, unsigned char byteno)//add one parameter more for selecting model/machine id
{
    
	unsigned int addrh ,addrl;
	//unsigned int datah,datal;
	unsigned char i;
	
	//for(i = 0; i <2; ++i)
	{
		addrh = addr;
		addrh >>= 8;     //only msb 
		addrl = (addr & 0x00FF); //lsb
	//START BIT	
		startBitGen();
    
    
    
	//SENDING BYTE	
		bytewrite(0xA0);
		bytewrite(addrh);
		bytewrite(addrl);
	    bytewrite(byteno);  //0x67
        //bytewrite(cmodelname_arr[0]);	
        
	
	//	bytewrite(datah);
	//	bytewrite(datal);		
	//STOP BIT***
		stopBitGen();	
		count_6ms = 0;
		addr++;
    
    
		while(count_6ms <= 12)
		{
            
		}	
	}		
		
}
void E2PWrite(unsigned int iAddr,unsigned char cNoOfByte, unsigned char* cDataArray)
{
    unsigned int addrh ,addrl;
	unsigned char i;
	for(i = 0; i < cNoOfByte; ++i)
	{
		addrh = iAddr;
		addrh >>= 8;     //only msb 
		addrl = (iAddr & 0x00FF); //lsb
	//START BIT	
		startBitGen();
	//SENDING BYTE	
		bytewrite(0xA0);
		bytewrite(addrh);
		bytewrite(addrl);
        bytewrite(cDataArray[i]);
	//STOP BIT***
		stopBitGen();	
		count_6ms = 0;
		iAddr++;
		while(count_6ms <= 12)
		{            
		}	
	}	
}
void E2PRead(unsigned int iAddr,unsigned char cNoOfByte)
{
	unsigned int addrh ,addrl;	
	unsigned char i;	
	for(i = 0; i < cNoOfByte; ++i)
	{
		addrh = iAddr;
		addrh >>= 8;
		addrl = (iAddr & 0x00FF);				
		startBitGen();
		bytewrite(0xA0);
		bytewrite(addrh);
		bytewrite(addrl);	
		startBitGen();
		bytewrite(0xA1);        
		cE2pArray[i] = byteread();
		NOACK();	
		stopBitGen();	
		iAddr++;
	}   
}
void I2C_Write2(unsigned int addr, unsigned char byteno, unsigned char field)
{
    unsigned int addrh ,addrl;
	//unsigned int datah,datal;
	unsigned char i,j;
	
	for(i = 0; i < byteno; ++i)
	{
		addrh = addr;
		addrh >>= 8;     //only msb 
		addrl = (addr & 0x00FF); //lsb
	//START BIT	
		startBitGen();
    
    
    
	//SENDING BYTE	
		bytewrite(0xA0);
		bytewrite(addrh);
		bytewrite(addrl);
	    //bytewrite(0x67);
        if(field==0)          //model name
        {
            for(j=0;j<15;j++)
            {
              bytewrite(cmodelname_arr[j]);
            }
        }
        else if(field==1)      //machine id
        {
            for(j=0;j<15;j++)  //11
            {
              bytewrite(ucRxPass[j]);
            }
        
        }    
        //bytewrite(cmodelname_arr[0]);	
        
	
	//	bytewrite(datah);
	//	bytewrite(datal);		
	//STOP BIT***
		stopBitGen();	
		count_6ms = 0;
		addr++;
    
    
		while(count_6ms <= 12)
		{
            
		}	
	}		


}
unsigned int I2C_Read(unsigned int addr ,unsigned char noofbytes,unsigned char* DataArray)
{
	unsigned int addrh ,addrl;	
	unsigned char i,tem[2],abc;

    for(i=0;i<noofbytes;++i)
    {
        addrh = addr;
        addrh >>= 8;
        addrl = (addr & 0x00FF);

        startBitGen();
        bytewrite(0xA0);
        bytewrite(addrh);
        bytewrite(addrl);	
        startBitGen();
        bytewrite(0xA1);
        DataArray[i]=byteread();//         abc = byteread();
        NOACK();	
        stopBitGen();	
        addr++;
        machineId_cnt++;
        if(DataArray[i] == '$')
        {
            return 0;
        }
    }
   
    return 0;
}    
unsigned int I2C_Read1(unsigned int addr ,unsigned char field)
{
	unsigned int addrh ,addrl;	
	unsigned char i,tem[2],abc;
	
	if(field==1)
    {
        //machineId_cnt=0;
        
        for(i=0;i<index;++i)
        {
            addrh = addr;
            addrh >>= 8;
            addrl = (addr & 0x00FF);

            startBitGen();
            bytewrite(0xA0);
            bytewrite(addrh);
            bytewrite(addrl);	
            startBitGen();
            bytewrite(0xA1);
            cmachineidR_arr[i]=byteread();//         abc = byteread();
            NOACK();	
            stopBitGen();	
            addr++;
            machineId_cnt++;
            if(cmachineidR_arr[i] == '$')
            {
                return 0;
            }
        }
    }
    else if(field==0)
    {
        //machineName_cnt = 0;
        
        //for(i=0;i<20;++i)
        {
            addrh = addr;
            addrh >>= 8;
            addrl = (addr & 0x00FF);

            startBitGen();
            bytewrite(0xA0);
            bytewrite(addrh);
            bytewrite(addrl);	
            startBitGen();
            bytewrite(0xA1);

            //cmodelnameR_arr[i]=byteread();//         abc = byteread();
            index=byteread();
            NOACK();	
            stopBitGen();	
            //addr++;
            //machineName_cnt++;
            
        }
    }
    else if(field==2)
    {
        machineI_cnt = 0;
        for(i=0;i<16;++i)
        {
            addrh = addr;
            addrh >>= 8;
            addrl = (addr & 0x00FF);

            startBitGen();
            bytewrite(0xA0);
            bytewrite(addrh);
            bytewrite(addrl);	
            startBitGen();
            bytewrite(0xA1);

            machineIR_arr[i]=byteread();//         abc = byteread();
            NOACK();	
            stopBitGen();	
            addr++;
            machineI_cnt++;
            if(machineIR_arr[i] == '$')
            {
                return 0;
            }  
        }
    }
    else if(field==3)
    {
        //machineI_cnt = 0;
        for(i=0;i<9;++i)
        {
            addrh = addr;
            addrh >>= 8;
            addrl = (addr & 0x00FF);

            startBitGen();
           // byteRTC_Write(0xA0);
            bytewrite(addrh);
            bytewrite(addrl);	
            startBitGen();
            bytewrite(0xA1);

            default_lat[i]=byteread();//         abc = byteread();
            NOACK();	
            stopBitGen();	
            addr++;
           /* machineI_cnt++;
            if(machineIR_arr[i] == '$')
            {
                return 0;
            } */ 
        }
    }
    else if(field==4)
    {
        //machineI_cnt = 0;
        for(i=0;i<10;++i)
        {
            addrh = addr;
            addrh >>= 8;
            addrl = (addr & 0x00FF);

            startBitGen();
            bytewrite(0xA0);
            bytewrite(addrh);
            bytewrite(addrl);	
            startBitGen();
            bytewrite(0xA1);

            default_long[i]=byteread();//         abc = byteread();
            NOACK();	
            stopBitGen();	
            addr++;
           /* machineI_cnt++;
            if(machineIR_arr[i] == '$')
            {
                return 0;
            } */ 
        }
    }
	//i=tem[1];
	return 0;
}

void RTC_Read()
{
    unsigned char j,cTemp; 
    startBitGen();
	bytewrite_rtc(0xA2);
    bytewrite_rtc(0x02);  //seconds
    stopBitGen();	
    startBitGen();
    bytewrite_rtc(0xA3);
    cTemp=byteread();
    cTemp= cTemp & 0x7F;    
    cDateTimeArray[13] = 0x30 + (cTemp & 0x0F);
    cTemp = cTemp >> 4;
    cDateTimeArray[12] = 0x30 + (cTemp & 0x0F);    
    NOACK();	
	stopBitGen();
    count_6ms = 0;
    while(count_6ms <= 12)
    {            
    } 
    startBitGen();
	bytewrite_rtc(0xA2);
    bytewrite_rtc(0x03);    //min
    stopBitGen();	
    startBitGen();
    bytewrite_rtc(0xA3);
    cTemp=byteread();
    cTemp= cTemp & 0x7F;    
    //cDateTimeArray[16] = ':';    
    cDateTimeArray[11] = 0x30 + (cTemp & 0x0F);
    cTemp = cTemp >> 4;
    cDateTimeArray[10] = 0x30 + (cTemp & 0x0F);   
    NOACK();	
	stopBitGen();
    count_6ms = 0;
    while(count_6ms <= 12)
    {            
    } 
    startBitGen();
	bytewrite_rtc(0xA2);
    bytewrite_rtc(0x04);     //hour
    stopBitGen();	
    startBitGen();
    bytewrite_rtc(0xA3);
    cTemp=byteread();
    cTemp= cTemp & 0x3F;    
    //cDateTimeArray[13] = ':';
    cDateTimeArray[9] = 0x30 + (cTemp & 0x0F);
    cTemp = cTemp >> 4;
    cDateTimeArray[8] = 0x30 + (cTemp & 0x0F);    
    NOACK();	
	stopBitGen();
    count_6ms = 0;
    while(count_6ms <= 12)
    {            
    }
    startBitGen();
	bytewrite_rtc(0xA2);
    bytewrite_rtc(0x05);       //date
    stopBitGen();	
    startBitGen();
    bytewrite_rtc(0xA3);
    cTemp=byteread(); 
    cTemp= cTemp & 0x3F;    
    cDateTimeArray[7] = 0x30 + (cTemp & 0x0F); //
    cTemp = cTemp >> 4;
    cDateTimeArray[6] = 0x30 + (cTemp & 0x0F);   // 
    NOACK();	
	stopBitGen();
    count_6ms = 0;
    while(count_6ms <= 12)
    {            
    }
    startBitGen();
	bytewrite_rtc(0xA2);
    bytewrite_rtc(0x07);          //month
    stopBitGen();	
    startBitGen();
    bytewrite_rtc(0xA3);
    cTemp=byteread();
    cTemp= cTemp & 0x1F;
    //cDateTimeArray[2] = '/';
    cDateTimeArray[5] = 0x30 + (cTemp & 0x0F);
    cTemp = cTemp >> 4;
    cDateTimeArray[4] = 0x30 + (cTemp & 0x0F);    
    NOACK();	
	stopBitGen();
    count_6ms = 0;
    while(count_6ms <= 12)
    {            
    } 

    startBitGen();
	bytewrite_rtc(0xA2);
    bytewrite_rtc(0x08);    //year
    stopBitGen();	
    startBitGen();
    bytewrite_rtc(0xA3);
    cTemp=byteread();
    //cDateTimeArray[5] = '/';
    cDateTimeArray[0] = '2';    //
    cDateTimeArray[1] = '0';    //
    cDateTimeArray[3] = 0x30 + (cTemp & 0x0F);
    cTemp = cTemp >> 4;
    cDateTimeArray[2] = 0x30 + (cTemp & 0x0F);  
    //cDateTimeArray[10] = ' ';
    NOACK();	
	stopBitGen();
    count_6ms = 0;
    while(count_6ms <= 12)
    {            
    }
    
}

void RTC_Write()
{
    
    startBitGen();  
    bytewrite_rtc(0xA2);    
    bytewrite_rtc(0x02);     //
    bytewrite_rtc(0x00);     //sec
    bytewrite_rtc(0x11);     // min
    bytewrite_rtc(0x11);    //hour    
    stopBitGen(); 

    count_6ms = 0;
    while(count_6ms <= 12)
    {            
    }
    
   startBitGen();   
    bytewrite_rtc(0xA2);    
    bytewrite_rtc(0x05);   
    bytewrite_rtc(0x04);   //28 date
    bytewrite_rtc(0x00);
    bytewrite_rtc(0x03);   //10 month
    bytewrite_rtc(0x22);   //21 year
    stopBitGen();  
    count_6ms = 0;
    while(count_6ms <= 12)
    {            
    }

}

void RTC_Write_Test()
{
    
    startBitGen();  
    bytewrite_rtc(0xA2);    
    bytewrite_rtc(0x02);     //
    bytewrite_rtc_Test(Sec);     //sec
    bytewrite_rtc_Test(Min);     // min
    bytewrite_rtc_Test(Hr);    //hour    
    stopBitGen(); 

    count_6ms = 0;
    while(count_6ms <= 12)
    {            
    }
    
   startBitGen();   
    bytewrite_rtc(0xA2);    
    bytewrite_rtc(0x05);   
    bytewrite_rtc_Test(Day);   //28 date
    bytewrite_rtc(0x00);
    bytewrite_rtc_Test(Month);   //10 month
    bytewrite_rtc_Test(Year);   //21 year
    stopBitGen();  
    count_6ms = 0;
    while(count_6ms <= 12)
    {            
    }

}

void bytewrite_rtc(unsigned char data)
{
    unsigned char temp,i;
	temp = data;	
	SDA1IO = 0;
    delayI2C();
    
	for(i=0;i<8;i++)
	{						
		temp = data;
		temp = temp << i;		
		SDA = (temp & 0x80) ? 1:0;
		delayI2C();	
			
		SCL = 1;
		delayI2C();					
		SCL = 0;
		delayI2C();		
	}		

    ACK_RTC();		


}
void bytewrite_rtc_Test(short int data)
{
    short int temp,i;
	temp = data;	
	SDA1IO = 0;
    delayI2C();
    
	for(i=0;i<8;i++)
	{						
		temp = data;
		temp = temp << i;		
		SDA = (temp & 0x80) ? 1:0;
		delayI2C();	
			
		SCL = 1;
		delayI2C();					
		SCL = 0;
		delayI2C();		
	}		

    ACK_RTC();		


}


void bytewrite(unsigned char data)
{
	unsigned char temp,i;
	temp = data;	
	SDA1IO = 0;
    delayI2C();
    
	for(i=0;i<8;i++)
	{						
		temp = data;
		temp = temp << i;		
		SDA = (temp & 0x80) ? 1:0;
		delayI2C();	
			
		SCL = 1;
		delayI2C();					
		SCL = 0;
		delayI2C();		
	}		

	ACK();		
			   
}
unsigned char byteread()
{
	unsigned char itemp,data,cnt;
	data = 0;
	SDA1IO = 1;	
	delayI2C();	
	for(cnt=0;cnt<8;cnt++)
	{		
		SCL = 1;
		delayI2C();	
		data <<= 1;
		data = (data | SDA_RD);		
//		if(SDA == 1)		
//		data |= 0x01;//|= (SDA & 0x01);
//		else 
//		data |= 0x00;	
//		data = (data << 1);
		  
		SCL = 0;
		delayI2C();		
	}
	SDA1IO = 0;	
	return data;	
}

void ACK()
{
	unsigned int cTimeout;
	SDA1IO = 0;
    delayI2C();
	SDA = 1;
	delayI2C();	
    SDA1IO= 1;
    
	SCL = 1;	
	delayI2C();	
	cTimeout = 0;
	//	
	delayI2C();				
	while(SDA_RD == 1)
	{
		cTimeout++;
		if(cTimeout >= 500)
		{
			//SDA = 0;
		}
	}
	SDA1IO = 0;
	SCL = 0;
	delayI2C();		
}

void ACK_RTC()
{
	unsigned int cTimeout;
    
    //delayI2C();
	//SDA1IO = 0;
    //delayI2C();
	SDA = 1;
	delayI2C();
    delayI2C();
    delayI2C();
    delayI2C();	
    
    //
    delayI2C();
	SCL = 1;	
	delayI2C();	
    SDA1IO= 1;
    delayI2C();
	cTimeout = 0;
	
	//delayI2C();				
	while(SDA_RD == 1)
	{
		cTimeout++;
		if(cTimeout >= 500)
		{
            SDA1IO= 0;
			SDA = 0;
            
		}
	}
	SDA1IO = 0;
	SCL = 0;
	delayI2C();		
}

void NOACK()
{
	SDA1IO = 1;
		
	SDA = 1;
	delayI2C();	
	SCL =1;
	delayI2C();
	SCL = 0;	
	delayI2C();
	SDA = 1;	
	delayI2C();		
}
void delayI2C()
{
    int k,l;
    l=0;
    for(k=0;k<100;k++)
    {
//        Nop();
        l++;
    }
}
void clock_simu()
{
    SCL = 1;
    
	delayI2C();
			
	SCL = 0;

}
