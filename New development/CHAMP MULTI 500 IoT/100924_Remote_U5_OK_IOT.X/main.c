/*
 * File:   main.c
 * Author: sm06
 * Created on June 9, 2021, 4:11 PM
 * PROJECT: IOT GATEWAY (PA79/680)
 */
/*****************************************************************************
//   DATE		WHO		REV			Description	
// 11-02-22		PPC		0.0		Added code to write MACHINE ID in EEPROM
// 18-02-22     PPC     0.0     Added code for ADC (AN2 & AN3 channel working)								
// 22-02-22     PPC     0.0     written a code to add Machine name & max current
//                              capacity of machine in to EEPROM.
// 13-04-22     PPC     0.0     Added function to convert NMEA format to degree decimal
//                              for GPS
// 22-04-22     PPC     0.0     Added Power ON 10 sec delay for ADC  
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include<sys/attribs.h>
#include "p32mx575f512l.h"
#include "function.c"
#include "define.c"
#include "VARIABLE2.c"
#include "SYSINIT.c"
#include "ISR2.c"
//#include "isr.C"
#include "IOT.c"
//#include "iot1.c"
#include "I2C.c"
#include "Wifi.c" 

//DEVCFG0 device configuration word 0
#pragma config CP        = OFF      //code protect bit-protection disabled-program memory read/modification by external programming device 
#pragma config BWP       = OFF      //boot flash write protect bit- protection disabled- boot flash memory modification during execution
#pragma config PWP       = OFF      //program flash write protect bit- protection disabled-
#pragma config ICESEL    = ICS_PGx1 // PGEC1 and PGED1 selected
#pragma config DEBUG     = OFF      //background debugger enable bit- debugger disabled

//DEVCFG1
#pragma config FWDTEN    = OFF      //wdt Enable bit-wdt disabled -canbe enabled in software
#pragma config WDTPS     = PS1      //wdt postscaler bit-wdt postscaler 1:1
#pragma config FCKSM     = CSDCMD   //clk switching/monitor selection configuration-disabled clk switch fscm
#pragma config FPBDIV    = DIV_1    //Pb_clk is Sys_clk/1
#pragma config OSCIOFNC  = OFF      //CLKO enable bit- clk out disabled
#pragma config POSCMOD   = HS       //CHECK*****************************************
#pragma config IESO      = OFF      //internal external switchover bit-disabled
#pragma config FSOSCEN   = OFF      //secondary oscillator enable bit-disabled
#pragma config FNOSC     = FRCPLL   //FAST RC OSCILLATOR WITH PLL

//DEVCFG2
#pragma config FPLLODIV  = DIV_2    //PLL output divided by 1
#pragma config UPLLEN    = OFF      //usb pll enable bit-disabled
#pragma config UPLLIDIV  = DIV_1    //usb pll divided by 1
#pragma config FPLLMUL   = MUL_24   //pll multiplier bits
#pragma config FPLLIDIV  = DIV_1    //pll input divider bits
//input divider is 2 by default. mltiplier 24 and output divider 2-> 8mhz/2=4   4*24=96mhz    96/2=48MHZ

//DEVCFG3
#pragma config FVBUSONIO = OFF      //usb Vbuson selection bit-disabled
#pragma config FUSBIDIO  = OFF
#pragma config FCANIO    = OFF 

void main()
{
    //for(j=0;j<100;j++)
	//for(i=0;i<20000;i++); 
    system_initialise();
    //for(j=0;j<100;j++)
	//for(i=0;i<20000;i++); 
    //i2cinit();
    //ReadMachine_details();
    //RTC_Read();
    
    //iValidGPSLocCNTR = VALIDLOCATIONDLY;
    power_ON_delay_f=1;
    while(1)
    {
        if(power_ON_delay_f==1)
            Wifi_initialisation();  
        
        if(ucSend_RemoteToPS==1)
        {
            ucSend_RemoteToPS=0;
            for(i=0;i<6;i++)
                TRANS5(rec_arr[i]);
        }
        if(ucSend_PSToRemote==1)
        {
            ucSend_PSToRemote=0;
            for(i=0;i<13;i++)
                TRANS2(rec_arr1[i]);
        }
        if(power_ON_delay_f==0)
            Wifi_Send_Data();
    }   
}



void trans_uart2(unsigned int data)
{
    while(U1STAbits.UTXBF==1);
    U1TXREG=data;
}

void send_AT()
{
        send_string_u1("AT");
		
		TRANS1(0x0D);
		TRANS1(0x0A);


}
void TRANS2(unsigned char data)  //edit as per uart requirement
{
	while(U2STAbits.UTXBF == 1);	
	U2TXREG=data;
    
}
void TRANS1(unsigned char data)  //edit as per uart requirement
{
	while(U1STAbits.UTXBF == 1);	
	U1TXREG=data;
    
}

void TRANS4(unsigned char data)  //edit as per uart requirement
{
	while(U4STAbits.UTXBF == 1);	
	U4TXREG=data;
    
}

void TRANS5(unsigned char data)  //edit as per uart requirement
{
	while(U5STAbits.UTXBF == 1);	
	U5TXREG=data;
    
}

void send_string_u1(char *s)
{
	while(*s)
	{
	   TRANS1(*s++);
	}
}

void send_string_u5(char *s)
{
	while(*s)
	{
	   TRANS5(*s++);
	}
}

void send_string_u2(char *s)
{
    while(*s)
    {
       TRANS2(*s++);
    }

}

void send_string_u4(char *s)
{
    while(*s)
    {
       TRANS4(*s++);
    }

}

void send_value(unsigned int value)
{
	unsigned int chigh=0, clow=0,cmiddle=0,chighest=0;
	unsigned int itemp=0;
    
	itemp=value;
	clow= itemp%10; //0x30 
	itemp /=10;
	cmiddle=itemp%10; //0x30 
	itemp /=10;
	chigh=itemp%10;  //0x30 
	itemp /=10;
	chighest=itemp;
	
	TRANS4(chighest+'0'); // UART4 Wi-Fi
	TRANS4(chigh+'0');
	TRANS4(cmiddle+'0');
	TRANS4(clow+'0');
}

void send_value_2(unsigned int value)
{
	unsigned char chigh=0, clow=0,cmiddle=0,chighest=0;
	unsigned int itemp=0;
	
	//for sending ascii value
	
	itemp=value;
	clow=0x30 + itemp%10;
	itemp /=10;
	cmiddle=0x30 + itemp%10;
	itemp /=10;
	chigh=0x30 + itemp%10;
	itemp /=10;
	chighest=0x30 + itemp;
	
	TRANS2(chighest);
	TRANS2(chigh);
	TRANS2(cmiddle);
	TRANS2(clow);
	
}

void send_value_4(unsigned int value)
{
	unsigned char chigh=0, clow=0,cmiddle=0,chighest=0;
	unsigned int itemp=0;
	
	//for sending ascii value
	
	itemp=value;
	clow=0x30 + itemp%10;
	itemp /=10;
	cmiddle=0x30 + itemp%10;
	itemp /=10;
	chigh=0x30 + itemp%10;
	itemp /=10;
	chighest=0x30 + itemp;
	
	TRANS4(chighest);
	TRANS4(chigh);
	TRANS4(cmiddle);
	TRANS4(clow);
	
}

void ADC_Read()
{
    static unsigned long sum_AN2_vtg=0,sum_AN3_vtg=0;
   
    
    sum_AN2_vtg = sum_AN2_vtg + result_AN2;
    sum_AN3_vtg = sum_AN3_vtg + result_AN3;
    adc_cnt++;
    if(adc_cnt>=1024)//1024 //512
    {
        adc_cnt=0;
        AN2_ADCValue = sum_AN2_vtg>>10;//10//9;
        AN3_ADCValue = sum_AN3_vtg>>10;//9;
        sum_AN2_vtg = 0;
        sum_AN3_vtg = 0;
        
        //for testing 
        #if 0
            TRANS2('@');
            high_byte=AN2_ADCValue;
            TRANS2(high_byte);
            low_byte=AN2_ADCValue>>8;
            TRANS2(low_byte);
            TRANS2('#');
            high_byte=AN3_ADCValue;
            TRANS2(high_byte);
            low_byte=AN3_ADCValue>>8;
            TRANS2(low_byte);
        #endif
               
            //adccurrent = (AN2_ADCValue * maxshunt)/ slope; //max adc count = 930 for 3V & slope = 9.30 
            //adcvoltage = (AN3_ADCValue * 10.0)/93.0;  //max adc count = 930 for 3V & slope = 93.0
            adccurrent = (AN2_ADCValue * maxshunt)/ slope; //max adc count = 930 for 3V & slope = 9.30 
            adcvoltage = (AN3_ADCValue * 100.0)/93.0;  //max adc count = 930 for 3V & slope = 93.0
            //if(iactualcurrent>10)
            
            iactualcurrent = adccurrent;
            iactualvoltage = adcvoltage;    
            
        /*    if(adccurrent>10)
            {
                weld_on_f = 1;
                lastcurrentf=1;
                iactualcurrent = adccurrent;
                iactualvoltage = adcvoltage;      
                count_5sec = 0;
                lastcurrent1f=0;
                memcpy(ctorch_status,"ON ",3);
            } 
            else 
            {
                //if(count_5sec>10000) //5 sec delay
                {    
                    memcpy(ctorch_status,"OFF",3);
                    weld_on_f = 0;
                    
                    if(lastcurrentf == 1)
                    {
                        iactualcurrent = preadccurrent;
                        iactualvoltage = preadcvoltage; 
                        lastcurrent1f=1;
                    }
                    else
                    {    
                        iactualcurrent=0;
                        iactualvoltage=0;
                    }
                    count_5sec=0;
                }    
            }  */ 
            if(adccurrent>10)
            {
                weld_on_f = 1;
            }  
            else
            {
                weld_on_f = 0;
            }    
            
            
            if(lastcurrent1f != 1 )//&& lastcurrent1f == 1)
            {
                preadccurrent = adccurrent;
                preadcvoltage = adcvoltage;
            }    
           
            
                
               
           
            #if 0
            if(adcflag == 1)
            { 
                TRANS2('@');
                high_byte=iactualcurrent;
                TRANS2(high_byte);
                low_byte=iactualcurrent>>8;
                TRANS2(low_byte);
                TRANS2('#');
                high_byte=iactualvoltage;
                TRANS2(high_byte);
                low_byte=iactualvoltage>>8;
                TRANS2(low_byte);
                adcflag=0;
            }
        #endif
            
    }    
}

void Append_data_analog()
{
    //if(Copy_IOT_data==1 && Send_IOT_data==0)
    {    
        Copy_IOT_data=0;
        if(weld_on_f == 1)
        {
            Int_to_ascii(iactualcurrent);
            cAcualcur[ucnt]= highest;
            cAcualcur[ucnt+1]= high;
            cAcualcur[ucnt+2]= middle;
            cAcualcur[ucnt+3]= low;
            cAcualcur[ucnt+4]= ',';

            Int_to_ascii(iactualvoltage);
            cActualvtg[ucnt]= highest;
            cActualvtg[ucnt+1]= high;
            cActualvtg[ucnt+2]= middle;
            cActualvtg[ucnt+3]= low;
            cActualvtg[ucnt+4]= ',';
            
            cWeld_status[tcnt]='W';
            cWeld_status[tcnt+1]='e';
            cWeld_status[tcnt+2]='l';
            cWeld_status[tcnt+3]='d';
            cWeld_status[tcnt+4]=' ';
            cWeld_status[tcnt+5]='O';
            cWeld_status[tcnt+6]='N';
            cWeld_status[tcnt+7]=' ';
            cWeld_status[tcnt+8]=',';

        }  
        else
        {
            cAcualcur[ucnt]= 0;
            cAcualcur[ucnt+1]= 0;
            cAcualcur[ucnt+2]= 0;
            cAcualcur[ucnt+3]= 0;
            cAcualcur[ucnt+4]= ',';

            cActualvtg[ucnt]= 0;
            cActualvtg[ucnt+1]= 0;
            cActualvtg[ucnt+2]= 0;
            cActualvtg[ucnt+3]= 0;
            cActualvtg[ucnt+4]= ',';

            cWeld_status[tcnt]  ='W';
            cWeld_status[tcnt+1]='e';
            cWeld_status[tcnt+2]='l';
            cWeld_status[tcnt+3]='d';
            cWeld_status[tcnt+4]=' ';
            cWeld_status[tcnt+5]='O';
            cWeld_status[tcnt+6]='F';
            cWeld_status[tcnt+7]='F';
            cWeld_status[tcnt+8]=',';
        } 
        ucnt = ucnt+5;
        tcnt = tcnt+9;
        IOTcnt++;
        if(IOTcnt>=15)
        {
            Send_IOT_data=1;
            IOTcnt=0;
            for(i=0;i<75;i++)
            {
                cAcualcur_Tx[i]=cAcualcur[i];
                cActualvtg_Tx[i]=cActualvtg[i];                
                cAcualcur[i]=0;
                cActualvtg[i]=0;        
                
            } 
            for(i=0;i<135;i++)
            {
                ctorch_status[i] = cWeld_status[i];
                cWeld_status[i] = 0;
            }    
            ucnt=0;
            tcnt=0;
            
        }    
    }
}
void Append_data_digital()
{
    Copy_IOT_data=0;
    //Int_to_ascii(iactualcurrent);
    cAcualcur[ucnt]= ActCurrent_str[0];//highest;
    cAcualcur[ucnt+1]= ActCurrent_str[1];//high;
    cAcualcur[ucnt+2]= ActCurrent_str[2];//middle;
    cAcualcur[ucnt+3]= ActCurrent_str[3];//low;
    cAcualcur[ucnt+4]= ',';

    //Int_to_ascii(iactualvoltage);
    cActualvtg[ucnt]= ActVoltage_str[0];//highest;
    cActualvtg[ucnt+1]= ActVoltage_str[1];//high;
    cActualvtg[ucnt+2]= ActVoltage_str[2];//middle;
    cActualvtg[ucnt+3]= ActVoltage_str[3];//low;
    cActualvtg[ucnt+4]= ',';

    cWeld_status[tcnt]  ='W';
    cWeld_status[tcnt+1]='e';
    cWeld_status[tcnt+2]='l';
    cWeld_status[tcnt+3]='d';
    cWeld_status[tcnt+4]=' ';
    cWeld_status[tcnt+5]=ctorch_status_mc[0];
    cWeld_status[tcnt+6]=ctorch_status_mc[1];
    cWeld_status[tcnt+7]=ctorch_status_mc[2];
    cWeld_status[tcnt+8]=',';
    
    ucnt = ucnt+5;
    tcnt = tcnt+9;
    IOTcnt++;
    if(IOTcnt>=15)//15
    {
        Send_IOT_data=1;
        IOTcnt=0;
        for(i=0;i<75;i++)//75
        {
            cAcualcur_Tx[i]=cAcualcur[i];
            cActualvtg_Tx[i]=cActualvtg[i];                
            cAcualcur[i]=0;
            cActualvtg[i]=0;        

        } 
        for(i=0;i<135;i++)//135
        {
            ctorch_status[i] = cWeld_status[i];
            cWeld_status[i] = 0;
        }    
        ucnt=0;
        tcnt=0;

    }    
}						  

void Int_to_ascii(unsigned int value)
{
    
    
	
	//for sending ascii value
	
	tempvalue=value;
	low=0x30 + tempvalue%10;
	tempvalue /=10;
	middle=0x30 + tempvalue%10;
	tempvalue /=10;
	high=0x30 + tempvalue%10;
	tempvalue /=10;
	highest=0x30 + tempvalue;
	
	/*temp_arr[0]=chighest;
	temp_arr[1]=(chigh);
	temp_arr[2]=(cmiddle);
	temp_arr[3]=(clow);*/
}

unsigned char Model_select()
{
    unsigned char count=0,ii=0,Model=0;

    while(machineIR_arr[count] != ',')
    {
        max_current_arr[count] = machineIR_arr[count];
        count++;
        if(count>10)   //added this condition if garbage value in machineIR_arr aaray
            break;
    } 
    if (strcmp(max_current_arr, "250") == 0)
    {
       //send_string_u2(" Model 250 ");
       Model = 'A';
       maxshunt = 2.5;
    }
    else if (strcmp(max_current_arr, "300") == 0)
    {
        //send_string_u2(" Model 300 ");
        Model = 'B';
        maxshunt = 3.0;
    }
    else if (strcmp(max_current_arr, "400") == 0)
    {
        //send_string_u2(" Model 400 ");
        Model = 'C';
        maxshunt = 4.0;
    }
    else if (strcmp(max_current_arr, "500") == 0)
    {
        //send_string_u2(" Model 500 ");
        Model = 'D';
        maxshunt = 5.0;
    }
    else if (strcmp(max_current_arr, "600") == 0)
    {
        //send_string_u2(" Model 600 ");
        Model = 'E';
        maxshunt = 6.0;
    }
    else if (strcmp(max_current_arr, "800") == 0)
    {
        //send_string_u2(" Model 800 ");
        Model = 'F';
        maxshunt = 8.0;
    }
    else if (strcmp(max_current_arr, "1200") == 0)
    {
        //send_string_u2(" Model 1200 ");
        Model = 'G';
        maxshunt = 12.0;
    }
    else
    {
        Model = 'X';
        maxshunt = 6.0;
    }    
    
    return Model;
    
    
   /* send_string_u2(" Machine current = ");
    for( ii=0;ii<count;ii++)
    {
       TRANS2(max_current_arr[ii]); 
    } */   
}

//Added this function to get DATE & TIME from GSM ARRAY


void ReadMachine_details()
{
    I2C_Read1(MACHINE_ID_ADDR,1);                   
    delayI2C();
    I2C_Read1(MODEL_NAME_ADDR,0);                  
    delayI2C();
    I2C_Read1(MACHINE_I_ADDR,2);
    delayI2C();
    I2C_Read1(LATITUDE_ADDR,3);
    delayI2C();
    I2C_Read1(LONGITUDE_ADDR,4);
    delayI2C();
    
  
    send_string_u2("Machine ID = ");
    for(i=0;i<machineId_cnt-1;i++)
    {
        TRANS2(cmachineidR_arr[i]);
    }
    send_string_u2(" Machine Name = ");
    for(i=0;i<machineName_cnt-1;i++)
    {
        TRANS2(cmodelnameR_arr[i]);
    }
    send_string_u2(" Machine Current = ");
    for(i=0;i<machineI_cnt-1;i++)
    {
        TRANS2(machineIR_arr[i]);
    }
    send_string_u2(" LATITUDE_ADDRESS = ");
    for(i=0;i<8;i++)
    {
        TRANS2(default_lat[i]);
    }
    send_string_u2(" LONGITUDE_ADDRESS = ");
    for(i=0;i<8;i++)
    {
        TRANS2(default_long[i]);
    }
    Machine_Model = Model_select();
    send_string_u2(" SOFTWARE REVISION = 1");
    //wifistrlen = strlen(wifiPOST); 
    //wifistrlen = strlen(cWifidata);
    //cWifistrlen = wifistrlen + '0';
    //send_string_u2(" str=");
    //send_value_2(wifistrlen);
    //TRANS2('@');
  /*  high_byte=wifistrlen;
    TRANS2(high_byte);
    low_byte=wifistrlen>>8;
    TRANS2(cWifistrlen);*/
    
    
}

//Added this function to convert NMEA format to degree decimal
void DecimalDegrees(const char *latLon,char quadrant,unsigned char latlonsel)
{
    unsigned long int tempv,MM;
    unsigned char sign;//,DD;
    unsigned long int dec;
    
    sign = ((quadrant=='S') || (quadrant=='W'))? 1:0;
    
    if(latlonsel == 1)
    {    
    
        MM = (((latLon[2]-0x30)*100000)+((latLon[3]-0x30)*10000)+((latLon[5]-0x30)*1000)+((latLon[6]-0x30)*100)+((latLon[7]-0x30)*10)+(latLon[8]-0x30));
        dec = (MM*100)/60;

        tempv = dec;
        TRANS2('$'); 
        GPS_lat_buf[0]=latLon[0];
        GPS_lat_buf[1]=latLon[1];
        for(i=8;i>=3;i--) 
        {    

            GPS_lat_buf[i-1]=0x30 + tempv%10;
            tempv /=10;
            
        }
        for(i=8;i>=5;i--)
        {
            GPS_lat_buf[i]= GPS_lat_buf[i-1];
        }  
        GPS_lat_buf[5-1]='.';
        
        if(sign == 1)
            GPS_lat_buf[0]='-';
        
        for(i=0;i<9;i++) 
        {    
            TRANS2(GPS_lat_buf[i]);
        }
            
    }
    else if(latlonsel == 2)
    {
        MM = (((latLon[3]-0x30)*100000)+((latLon[4]-0x30)*10000)+((latLon[6]-0x30)*1000)+((latLon[7]-0x30)*100)+((latLon[8]-0x30)*10)+(latLon[9]-0x30));
        dec = (MM*100)/60; 
        TRANS2('@'); 
        tempv = dec;
        GPS_long_buf[0] = latLon[0];
        GPS_long_buf[1] = latLon[1];
        GPS_long_buf[2] = latLon[2];       
        
        for(i=8;i>=3;i--)     
        {    
            GPS_long_buf[i]=0x30 + tempv%10;
            tempv /=10;
        }
        for(i=9;i>=5;i--)
        {
            GPS_long_buf[i]= GPS_long_buf[i-1];
        }  
        GPS_long_buf[6-1]='.';
        
        if(sign == 1)
            GPS_long_buf[0]='-';
        
        for(i=0;i<10;i++) 
        {    
            TRANS2(GPS_long_buf[i]);
        }
    }            
    
}

void DisplayJasonLineOnTerminal(unsigned int cLineNo)
{
    unsigned char count;
    
    switch(cLineNo)
    {
    case 2:
        TRANS2(0x22); //"
        send_string_u2("AuthKey");
        TRANS2(0x22); //"
        TRANS2(0x3A); //:

        TRANS2(0x22); //"
        send_string_u2("c3ltcGhvbnk=");
        TRANS2(0x22);
        TRANS2(0x0D);        
        break;
    case 3:
		TRANS2(0x22); //"
		send_string_u2("MachineName");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
        count = 0;
        while(count<machineName_cnt-1)    
        {
         TRANS2(cmodelname_arr[count]); 
         count++;
        }
		TRANS2(0x22); //"        
        TRANS2(0x0D);
        break;
    case 4:
		TRANS2(0x22); //"
		send_string_u2("MachineID");
        //TRANS2('@');
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
        count=0;
        for(i=0;i<11;i++)//while(count<11)
        {
         TRANS2(cmachineidR_arr[i]); 
         //TRANS2(cmachineidR_arr[i]);
         //count++;
        }
		//send_string_u2("79/20210001"); //79/20210001//73/21126789// 73/211223445 // 73/21068753 
		TRANS2(0x22); //"
        TRANS2(0x0D);
        break;
    case 5:
		TRANS2(0x22); //"
		send_string_u2("Software Revision");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		count=0;
        while(count<3)
        {
         TRANS2(softrev_str[count]); 
         count++;
        }
        //send_string_u2("REV2.1");
		TRANS2(0x22); //"
        TRANS2(0x0D);
        break;
    case 6:
		TRANS2(0x22); //"
		send_string_u2("Command Number");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		send_string_u2("0");
		TRANS2(0x22); //"
        TRANS2(0x0D);
        break;
    case 7:
		TRANS2(0x22); //"
		send_string_u2("Xaxis");    //Latitude
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
        count=0;
        if(default_locf==1)  //valid data from gps module
        {
            while(count<9)
            {
             TRANS2(latdata[count]); 
             count++;
            }
        }
        else
        {
            while(count<9)
            {
             TRANS2(default_lat[count]); 
             count++;
            }
        
        }
		TRANS2(0x22); //"        
        TRANS2(0x0D);
        break;
    case 8:
		TRANS2(0x22); //"
		send_string_u2("Yaxis");   //Longitude
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		//send_string_u1("73.650952");  //073.78768
        
        count=0;
        if(default_locf==1)  //valid data from gps module
        {
            while(count<9)
            {
             TRANS2(longdata[count]); 
             count++;
            }
        }
        else
        {
            while(count<8)
            {
             TRANS2(default_long[count]); 
             count++;
            }
        
        }
		TRANS2(0x22); //"
        TRANS2(0x0D);
        break;
    case 9:
		TRANS2(0x22); //"
		send_string_u2("Process");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
        count=0;
        while(count<13)//(twot_str[count]!='\0') //8
        {
           TRANS2(process_str[count]);
           count++;
        }
		//send_string_u2("MIG/MAG");
		TRANS2(0x22); //"
        TRANS2(0x0D);
        break;
    case 10:
		TRANS2(0x22); //"
		send_string_u2("WeldMode");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
        count=0;
        while(count<2)//(twot_str[count]!='\0')
        {
           TRANS2(twot_str[count]);
           count++;
        }
		//send_string_u2("4T");
		TRANS2(0x22); //"
        TRANS2(0x0D);
        break;
    case 11:
		TRANS2(0x22); //"
		send_string_u2("Wire Speed");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		//send_string_u2("23.2");
		send_value_2(iwirespeed);
		TRANS2(0x22); //"
        TRANS2(0x0D);        
        break;
    case 12:
		TRANS2(0x22); //"
		send_string_u2("SetCurrent");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		//send_string_u2("0165");
		send_value_2(isetcurrent);
		TRANS2(0x22); //"
        TRANS2(0x0D);        
        break;
    case 13:
		TRANS2(0x22); //"
		send_string_u2("SetVoltage");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		//send_string_u2("024.3");
		send_value_2(isetvoltage);
		TRANS2(0x22); //"
        TRANS2(0x0D);        
        break;
    case 14:
		TRANS2(0x22); //"
		send_string_u2("Metal");   //Material
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
        count=0;
        while(count<6)//(cmaterial_str[count]!='\0')
        {
           TRANS2(cmaterial_str[count]);
           count++;
        }
		//send_string_u2("MSFCAW");
		TRANS2(0x22); //"
        TRANS2(0x0D);        
        break;
    case 15:
		TRANS2(0x22); //"
		send_string_u2("Diameter");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		count=0;
        while(count<3)//(twot_str[count]!='\0')
        {
           TRANS2(cdia_str1[count]); 
           count++;
        }
       // send_string_u2("1.2");
		TRANS2(0x22); //"
        TRANS2(0x0D);        
        break;
    case 16:
		TRANS2(0x22); //"
		send_string_u2("Gas");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
        count=0;
        while(count<12)//(cgas_str[count]!='\0')
        {
           TRANS2(cgas_str[count]);
           count++;
        }
		//send_string_u2("AR");
		TRANS2(0x22); //"
        TRANS2(0x0D);        
        break;
    case 17:
		TRANS2(0x22); //"
		send_string_u2("HF");  //HF Status
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		send_string_u2("OFF");
		TRANS2(0x22); //"
        TRANS2(0x0D);        
        break;
    case 18:
		TRANS2(0x22); //"
		send_string_u2("Carriage");  //Carriage Status
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		send_string_u2("OFF");
		TRANS2(0x22); //"
        TRANS2(0x0D);        
        break;
    case 19:
		TRANS2(0x22); //"
		send_string_u2("Carriage Speed");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		send_string_u2("02.5");
		TRANS2(0x22); //"
        TRANS2(0x0D);        
        break;
    case 20:
		TRANS2(0x22); //"
		send_string_u2("Time");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
        //send_string_u2(" IOT = ");
        for(i = 0; i < 14; ++i)
        {
            TRANS2(cDateTimeArray[i]);
            //TRANS2(cDateTimeArray[i]);
        }
		//send_string_u2("20220226124950");
		TRANS2(0x22); //"
        TRANS2(0x0D);        
        break;
    case 21:
		TRANS2(0x22); //"
		send_string_u2("Welding");  //Status
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
        send_string_u2("Weld ");
		count=0;
        if(weld_on_f==1)//(weldon_off == 1 )
        {
           send_string_u2("ON");    
        } 
        else// if(weldon_off == 2 )
        {
           send_string_u2("OFF");    
        } 
        
		TRANS2(0x22); //"
        TRANS2(0x0D);        
        break;
    case 22:
		TRANS2(0x22); //"
		send_string_u2("ActualCurrent");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		//send_string_u2("176");
		send_value_2(iactualcurrent);
       // send_value_2(iactualcurrent);
		TRANS2(0x22); //"
        TRANS2(0x0D);        
        break;
    case 23:
		TRANS2(0x22); //"
		send_string_u2("ActualVoltage");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		//send_string_u2("21.5");
		send_value_2(iactualvoltage);
        //send_value_2(iactualvoltage);
		TRANS2(0x22); //"
        TRANS2(0x0D);        
        break;
    case 24:
		TRANS2(0x22); //"
		send_string_u2("Error");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
        switch(error_str[2])
        {
            case '1':
                send_string_u2("Under Voltage");
                break;
            case '2':
                send_string_u2("Over Voltage");
                break;
            case '3':
                send_string_u2("Thermal Error");
                break;
            case '4':
                send_string_u2("No Current");
                break;
            case '5':
                send_string_u2("Motor Overload");
                break;
            case '7':
                send_string_u2("Pressure Error");
                break;
            case '8':
                send_string_u2("Communication error");
                break;
            default:
                send_string_u2("No Error");
                break;
        
        
        }
		//send_string_u1("No Error");
		TRANS2(0x22); //"        
        TRANS2(0x0D);        
        break;
    case 25:
		TRANS2(0x22); //"
		send_string_u2("ARCONTIME");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		//send_string_u1("18:34");
        count=0;
        while(count<3)
        {
           TRANS2(arcontime_str[count]); 
           count++;
        
        }
		TRANS2(0x22); //"
        TRANS2(0x0D);        
        break;        
    default:
        
        
        TRANS2(0x0D);        
        break;













        
    }
    
    
    
}