#include "p32mx575f512l.h"

void __ISR(_TIMER_2_VECTOR, IPL7SRS)T2Interrupt(void) //7 highest priority
{
    IFS0bits.T2IF=0;     //0.5MSEC
    ihalf_sec_count++;
    ifive_sec_count++;
    count_6ms++;
    
    if(ihalf_sec_count>=1000)
    {
      ihalf_sec_count=0;
      chalf_sec=1;
       /*if(chalf_sec==1)
        {
            PORTGINV=0X0001;
            chalf_sec=0;
        }*/
      
    }
    if(ifive_sec_count>=8000)
    {
        cfive_sec=1;
        ifive_sec_count=0;
        adcflag=1;
    }  
    
        

}

void __ISR(_TIMER_1_VECTOR, IPL7SRS)T1Interrupt(void)
{
    
    //IFS0CLR=0X0010;            //1MSEC
    IFS0bits.T1IF=0;
    ione_sec_count++;
    fifty_sec++;
    transmit_modem++;
    tx_one_sec++;
    gprs_command_cnt++;
    power_ON_delay++;
    iCount_1Sec++;
    
    
    if(iValidGPSLocCNTR == 0)
    {
        PORTGINV |= 0X0002;
        if(cValidGPSLocFG == 1)
        {
            iValidGPSLocCNTR = VALIDLOCATIONDLY;
        }
        else
        {
            iValidGPSLocCNTR = INVALIDLOCATIONDLY;                
        }
    }
    else
        iValidGPSLocCNTR--;
    
    if(ione_sec_count>=1000)
    {
      ione_sec_count=0;
      Copy_IOT_data=1;
      cone_sec=1;
      cCount_15Sec++;   //count to send data after every 15 sec
      count_20sec++;               //POWER ON DELAY FOR ADC
      /*if(cCount_15Sec>=15)
      {
          cCount_15Sec=0;
          Send_IOT_data=1;
      } */
      if(count_20sec>20)
      {
          Pwron_delay_adc=1;
      }    
    }
    
    if(send_ATcmdFlag==1)
    {
        count_5min++;  
        if(count_5min>5000)//1000     1 sec
        {
            count_5min1++;
            send_ATcmdFlag=0;
            count_5min=0;
        }
    } 
    
    if(GSM_Time_cmd == 1)
    {    
        //LD2_IOLAT=0;
        count_1min++;
        if(count_1min>60000)
        {
            count_1min=0;
            count_60min++;
            if(count_60min>=59)//59
            {
                //LD2_IOLAT=1;
                count_60min=0;
                GSM_Time_cmd=0;
                chk_RTC_time=1;
            }    
        }
    }
    
    if(count_5min1>=2)
    {
        
        if(weldon_off == 1)
        {
            weldon_off=2;
        } 
        else if(weldon_off == 2)
        {
            weldon_off=1;
        } 
            
        count_5min1=0;
        
    }    
    /*if(decode_delay_f==1)    //decode delay of 100msec starts
    {
	    if(decode_Delay==0)
	    {
	       decode_delay_f=0;
	       decode_psdata_f=1;
	       
	    }
	    else
	    {
	       decode_Delay--;
	    
	    }
    
    
    
    }*/
    if(transmit_modem>=5000)                //5 sec
    {
       transmit_to_modem_rdy=1;
       transmit_modem=0;
    }
    if(gprs_command_cnt>=3000)  //4000//2 changed by PPC
    {
	    gprs_command_f=1;
	    gprs_command_cnt=0;
    
    }
    if(fifty_sec>=50000)
    {
        fifty_sec=0;
    }
    if(power_ON_delay>=10000)  //delay for modem
    {
       //power_ON_delay=0;
      // power_ON_delay_f=1;
    }  
    //if(GSM_Time_cmd == 1)
    {
        GSM_time++;
        if(GSM_time>=1000)
        {
            GSM_1sec++;
            GSM_time=0;
        }
    }    

}
void __ISR(_UART_1_VECTOR, IPL6SRS)_UART1Handler(void)          
{
    //unsigned char i;
    RX_data=U1RXREG;
    PORTAINV=0X0040;
    
    if(RX_data=='$')
    {
    //cmodem_data=1;
    }

    //PORTGINV=0X0001;
    IFS0bits.U1RXIF=0;
    //if((RX_data=='@'))
    //RX_data=0;
}


void __ISR(_UART_2_VECTOR, IPL7SOFT)_UART2Handler(void)          
{
    uartdata=U2RXREG;       
    IFS1bits.U2RXIF=0;
    
    if(uartdata=='$' && recstrtptr==0)   
    {
        reccnt=0;
        rec_arr[reccnt]=uartdata;
        recstrtptr=1;
        ione_sec_count=0;
        sendtoremotef=0;
     }
     else if(recstrtptr==1)
     {
        reccnt++;
        rec_arr[reccnt]=uartdata;
        if(reccnt==5)
        {
          reccnt=0;
          recstrtptr=0;
          ucSend_RemoteToPS=1;
        }  
     }    
}

void __ISR(_UART_4_VECTOR, IPL7SOFT)_UART4Handler(void)          
{
    cdatafrom_Wifi=U4RXREG;
    IFS2bits.U4RXIF=0; 
    switch(Wifi_response)
    {
        case 0:if(cdatafrom_Wifi=='O')
                {
                  Wifi_response=1;
                }
                else if(cdatafrom_Wifi=='E')
                  Wifi_response=2;
                else
                {
                  Wifi_response=0;
                  cdatafrom_Wifi=0;  
                }
                break;
         case 1:if(cdatafrom_Wifi=='K')
                {
                    ucWiFiOk=1;
                    Wifi_response=0; cdatafrom_Wifi=0; 
                }
                else
                {
                 Wifi_response=0;
                 cdatafrom_Wifi=0;  
                }
                break;
         case 2:if(cdatafrom_Wifi=='R')
                    Wifi_response=3;
                else
                {
                 Wifi_response=0;
                 cdatafrom_Wifi=0;  
                }
                break;
        case 3:if(cdatafrom_Wifi=='R')
                    Wifi_response=4;
                else
                {
                 Wifi_response=0;
                 cdatafrom_Wifi=0;  
                }
                break;
        case 4:if(cdatafrom_Wifi=='O')
                    Wifi_response=5;
                else
                {
                 Wifi_response=0;
                 cdatafrom_Wifi=0;  
                }
                break;
         case 5:if(cdatafrom_Wifi=='R')
                {
                    Wifi_response=0;
                    if((WifiSend)&&(power_ON_delay_f==0))
                    {
                        ATcommand=0;send_ATcmdFlag=0;count_5min=0; ucWiFiOk=0;power_ON_delay_f=0;
                    }
                }
                else
                {
                 Wifi_response=0;
                 cdatafrom_Wifi=0;  
                }
                break;
        default: break;
    }
}
            
void __ISR(_UART_5_VECTOR, IPL7SOFT)_UART5Handler(void)            //IPL7SOFT
{ 
   uartdata1=U5RXREG;
   IFS2bits.U5RXIF=0; 
   PORTAINV=0X0040;
   //ucSend_PSToRemote=1;
   if(uartdata1=='$' && recstrtptr1==0)
   {
      reccnt1=0;
      rec_arr1[reccnt1]=uartdata1;
      recstrtptr1=1;
      
   }
   else if (recstrtptr1==1)
   {
      reccnt1++;
      rec_arr1[reccnt1]=uartdata1;
      if(reccnt1==12)
      {
        reccnt1=0;
        recstrtptr1=0;
        ucSend_PSToRemote=1;
        SetVoltage=(unsigned int)(rec_arr1[3]+(rec_arr1[4]<<8)); 
        SetCurrent=(unsigned int)(rec_arr1[7]+(rec_arr1[8]<<8));
        SetWiSpeed=(unsigned int)(rec_arr1[5]+(rec_arr1[6]<<8));
      }
   }
}

void __ISR(_ADC_VECTOR, IPL2SOFT) _ADC_Handler(void)
{
    result_AN2 = (ADC1BUF0+ADC1BUF2+ADC1BUF4+ADC1BUF6)/4;
    result_AN3 = (ADC1BUF1+ADC1BUF3+ADC1BUF5+ADC1BUF7)/4;
    IFS1bits.AD1IF = 0; //   
    adc_readf=1;
    //TRANS2('#');
}