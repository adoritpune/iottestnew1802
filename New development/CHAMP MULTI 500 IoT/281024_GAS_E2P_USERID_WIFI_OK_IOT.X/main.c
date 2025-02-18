/*
 * File:   main.c
 * Author: RR & KK
 * Created on 07,11, 2024
 * PROJECT: IOT GATEWAY (PA79/680)
 */
/*****************************************************************************
//   DATE		WHO		REV			Description	
// 11-02-22		PPC		0.0		Added code to write MACHINE ID in EEPROM
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <xc.h>
#include<sys/attribs.h>
#include "p32mx575f512l.h"
#include "function.c"
#include "define.c"
#include "VARIABLE2.c"
#include "SYSINIT.c"
#include "ISR2.c"
//#include "IOT.c"
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
    system_initialise(); 
    i2cinit();
    RTC_Read();
    //iValidGPSLocCNTR = VALIDLOCATIONDLY;
    I2C_Read1(INDEX_ID_ADDR,0);
  
    send_value(index);
    //TRANS4('<');
    I2C_Read1(USER_ID_ADDR,1);
    for(i=0;i<index;i++)
    {
        TRANS4(cmachineidR_arr[i]);
    }
    //TRANS4('>');
    
    power_ON_delay_f=1;WifiSend=0,send_ATcmdFlag=0;
    
    while(1)
    {
        GASFLOW_MEASURMENT();
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
        {
            Wifi_Send_Data();
            IOT_control_send_data();
        }
    }   
}

void trans_uart2(unsigned int data)
{
    while(U1STAbits.UTXBF==1);
    U1TXREG=data;
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
	clow= itemp%10;         //0x30 
	itemp /=10;
	cmiddle=itemp%10;       //0x30 
	itemp /=10;
	chigh=itemp%10;         //0x30 
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

void send_valueID(unsigned int value)
{
	unsigned char chigh=0, clow=0,cmiddle=0,chighest=0;
	unsigned int itemp=0;
	
	//for sending ascii value
	
	itemp=value;
	clow=0x30 + itemp%10;
	itemp /=10;
	chigh=0x30 + itemp%10;
	
	TRANS4(chigh);
	TRANS4(clow);
	
}

/*void ADC_Read()
{
    static unsigned long sum_AN2_vtg=0,sum_AN3_vtg=0;
   
    
    sum_AN2_vtg = sum_AN2_vtg + result_AN2;
    //sum_AN3_vtg = sum_AN3_vtg + result_AN3;
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
          /*  if(adccurrent>10)
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
}*/

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

void ReadMachine_details()
{
    I2C_Read1(USER_ID_ADDR,1);                   
    delayI2C();
//    I2C_Read1(MODEL_NAME_ADDR,0);                  
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



