#include "p32mx575f512l.h"

void __ISR(_TIMER_2_VECTOR, IPL7SRS)T2Interrupt(void) //7 highest priority
{
    IFS0bits.T2IF=0;     //0.5MSEC
   
    //ihalf_sec_count++;
    //ifive_sec_count++;
    count_6ms++;
    
  /*  if(ihalf_sec_count>=1000)
    {
      ihalf_sec_count=0;
      chalf_sec=1;
       /*if(chalf_sec==1)
        {
            PORTGINV=0X0001;
            chalf_sec=0;
        }
      
    }*/
    /*
    if(ifive_sec_count>=8000)
    {
        //cfive_sec=1;
        ifive_sec_count=0;
        adcflag=1;
    }  
     */
}

void __ISR(_TIMER_1_VECTOR, IPL7SRS)T1Interrupt(void)
{
    //IFS0CLR=0X0010;            //1MSEC
    IFS0bits.T1IF=0;
    //ione_sec_count++;
    //fifty_sec++;
    //transmit_modem++;
    //tx_one_sec++;
    //gprs_command_cnt++;
    //power_ON_delay++;
    //iCount_1Sec++;
    
  /*  if(iValidGPSLocCNTR == 0)
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
   */ 
 /*   if(ione_sec_count>=1000)
    {
      ione_sec_count=0;
      Copy_IOT_data=1;
      cone_sec=1;
      cCount_15Sec++;   //count to send data after every 15 sec
      count_20sec++;    //POWER ON DELAY FOR ADC
    
      if(count_20sec>20)
      {
          Pwron_delay_adc=1;
      }    
    }*/
    
    if(send_ATcmdFlag==1)
    {
        count_5min++;  
        if(count_5min>500)//1000     1 sec
        {
            count_5min1++;
            send_ATcmdFlag=0;
            count_5min=0;
        }
    } 
    
/*    if(GSM_Time_cmd == 1)
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
    }*/
    
 /*   if(count_5min1>=2)
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
        
    }   */ 
    
   /* if(transmit_modem>=5000)                //5 sec
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
    }*/
  /*  if(power_ON_delay>=10000)  //delay for modem
    {
       power_ON_delay=0;
       //power_ON_delay_f=1;
    } */ 
    
    /*if(GSM_Time_cmd == 1)
    {
        GSM_time++;
        if(GSM_time>=1000)
        {
            GSM_1sec++;
            GSM_time=0;
        }
    }*/    

}
void __ISR(_UART_1_VECTOR, IPL6SRS)_UART1Handler(void)          
{
    RX_data=U1RXREG;
    PORTAINV=0X0040;
    //PORTGINV=0X0001;
    IFS0bits.U1RXIF=0;
}

void __ISR(_UART_2_VECTOR, IPL7SOFT)_UART2Handler(void)    // Remote to Iot Board      
{
    uartdata=U2RXREG;       
    IFS1bits.U2RXIF=0;

    if(uartdata=='$' && recstrtptr==0)   
    {
        reccnt=0;
        rec_arr[reccnt]=uartdata;
        recstrtptr=1;
        //ione_sec_count=0;
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

void __ISR(_UART_4_VECTOR, IPL7SOFT)_UART4Handler(void)        // WIFI Communication  
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
                else if(cdatafrom_Wifi=='@')
                  Wifi_response=1;
                else if(cdatafrom_Wifi=='?')
                  Wifi_response=8; 
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
                else if(cdatafrom_Wifi=='P')
                {
                  Wifi_response=6;
                  ucPcnt=0;
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
                    if((WifiSend>2)&&(power_ON_delay_f==0))
                    {
                        ATcommand=0;send_ATcmdFlag=0;count_5min=0; ucWiFiOk=0;power_ON_delay_f=1;WifiSend=0;
                    }
                }
                else
                {
                 Wifi_response=0;
                 cdatafrom_Wifi=0;  
                }
                break;
         case 6:if(cdatafrom_Wifi!=',')
                {  
                    ucRxPass[ucPcnt]=cdatafrom_Wifi;
                    ucPcnt++;
                }
                if(cdatafrom_Wifi==',')
                {
                    //ucPIndex=ucPcnt;ucPass=1;                    
                    ucRxPass[ucPcnt]=cdatafrom_Wifi;
                    ucPcnt++;
                    Wifi_response=7;
                    //ucPcnt=0;
                }
                break;
         case 7:if(cdatafrom_Wifi!=',')
                {                   
                    ucRxPass[ucPcnt]=cdatafrom_Wifi;
                    ucPcnt++;
                }
                if(cdatafrom_Wifi==',')
                {
                    ucPIndex=ucPcnt;ucPass=1;
                    Wifi_response=0;
                    ucPcnt=0;
                }
                break;
         case 8:if(cdatafrom_Wifi=='Q')
                  Wifi_response=9; 
                else
                  Wifi_response=0;
                break;
         case 9:switch(cdatafrom_Wifi)
                {
                    case 'P':Wifi_response=10;  // Program
                        break;
                    case 'W':ucPcnt=0;  
                             Wifi_response=11;  // SET Wire speed
                        break;
                    case 'V':ucPcnt=0;  
                             Wifi_response=12;  // SET Voltage
                        break;
                    case 'D':Wifi_response=13;  // Wire Diameter
                        break;
                    case 'M':Wifi_response=14;  // MODE - 2t or more
                        break;
                    case 'C':Wifi_response=15;  // Material
                        break;
                    case 'G':Wifi_response=16;  // GAS
                        break;
                    case 'A':Wifi_response=17;  // Auto Manual
                        break;
                    case 'I':ucPcnt=0; 
                             Wifi_response=18;  // MMA SET Current
                        break;
                    case 'F':ucPcnt=0; 
                             Wifi_response=19;  // Arc Force
                        break;
                    case 'R':Wifi_response=20;  // Arc Force ON /OFF
                        break;
                    case 'T':ucPcnt=0; 
                             Wifi_response=21;  // TIG SET Current
                        break;
                    case 'L':ucPcnt=0; 
                             Wifi_response=22;  // LOCk and Password
                        break;
                    case 'Y':ucPcnt=0; 
                             Wifi_response=23;  // Disable Password
                        break;
                    case 'J':ucPcnt=0; 
                             Wifi_response=24;  // Save JOB with Number
                        break;
                    case 'X':ucPcnt=0; 
                             Wifi_response=25;  // Recall JOb Number with parameter
                        break;
                    default :Wifi_response=0;
                        break;
                }
                break;
         case 10:ucPROG=cdatafrom_Wifi;
                IOT_control=1;
                Wifi_response=0;
                break;
         case 11:ucWS[ucPcnt]=cdatafrom_Wifi;
                 ucPcnt++;
                 if(ucPcnt==3)
                 {
                    IOT_control=2;
                    Wifi_response=0;ucPcnt=0;  
                 }
                break;
         case 12:ucSetV[ucPcnt]=cdatafrom_Wifi;
                 ucPcnt++;
                 if(ucPcnt==3)
                 {
                    IOT_control=3;
                    Wifi_response=0;ucPcnt=0;    //ucSetV
                 }
                break;
         case 13:ucWireDiameter=cdatafrom_Wifi;  // Wire Diameter
                IOT_control=4;
                Wifi_response=0;
                break;
         case 14:ucMode=cdatafrom_Wifi;          // MODE  
                IOT_control=5;
                Wifi_response=0;
                break;
         case 15:ucMaterial=cdatafrom_Wifi;      // Material 
                IOT_control=6;
                Wifi_response=0;
                break;
         case 16:ucGas=cdatafrom_Wifi;            // GAS  
                IOT_control=7;
                Wifi_response=0;
                break;
         case 17:ucAuto_MANUAL=cdatafrom_Wifi;    // ucAuto_MANUAL  
                IOT_control=8;
                Wifi_response=0;
                break;
         case 18:ucMMA_Current[ucPcnt]=cdatafrom_Wifi; // MMA SET Current
                 ucPcnt++;
                 if(ucPcnt==3)
                 {
                    IOT_control=9;
                    Wifi_response=0;ucPcnt=0;  
                 }
                break;
          case 19:ucArc_Force[ucPcnt]=cdatafrom_Wifi;          // Arc Force
                 ucPcnt++;
                 if(ucPcnt==3)
                 {
                    IOT_control=10;
                    Wifi_response=0;ucPcnt=0;  
                 }
                break;
          case 20:ucArcForceON_OFF=cdatafrom_Wifi;              // Arc Force On/OFF 
                IOT_control=11;
                Wifi_response=0;
                break;
          case 21:ucTIG_Current[ucPcnt]=cdatafrom_Wifi;         // TIG SET Current
                 ucPcnt++;
                 if(ucPcnt==3)
                 {
                    IOT_control=12;
                    Wifi_response=0;ucPcnt=0;  
                 }
                break;
          case 22:ucPassword[ucPcnt]=cdatafrom_Wifi;         // TIG SET Current
                 ucPcnt++;
                 if(ucPcnt==3)
                 {
                    IOT_control=13;
                    Wifi_response=0;ucPcnt=0;  
                 }
                break;
         case 23:ucLockDisable=cdatafrom_Wifi;     // ucAuto_MANUAL  
                IOT_control=14;
                Wifi_response=0;
                break;
         case 24:ucSJ[ucPcnt]=cdatafrom_Wifi; // Save Job Number
                 ucPcnt++;
                 if(ucPcnt==2)
                 {
                    IOT_control=15;
                    Wifi_response=0;ucPcnt=0;  
                 }
                break;
         case 25:ucRJ[ucPcnt]=cdatafrom_Wifi; // Recall JOB
                 ucPcnt++;
                 if(ucPcnt==2)
                 {
                    IOT_control=16;
                    Wifi_response=0;ucPcnt=0;  
                 }
                break;
        default: break;
    }
}

void __ISR(_UART_5_VECTOR, IPL7SOFT)_UART5Handler(void)            //Power Source To IOT Board
{ 
   uartdata1=U5RXREG;
   IFS2bits.U5RXIF=0; 
   PORTAINV=0X0040;
   //ucSend_PSToRemote=1;
   
   switch(recstrtpt_Iot)
   {
       case 0:if(uartdata1=='*')
              {
                 recstrtpt_Iot=1;IoT_reccnt=0;
                 rec_arr_IoT[IoT_reccnt]=uartdata1;
              }
              else if(uartdata1=='$')
              {
                recstrtpt_Iot=3;reccnt1=0; 
                rec_arr1[reccnt1]=uartdata1;
              }
              else
                  recstrtpt_Iot=0;
           break;
       case 1:if(uartdata1=='Z')
               {
                   recstrtpt_Iot=2;//IoT_reccnt=1;
                  // rec_arr_IoT[IoT_reccnt]=uartdata1;
               }
               else
                   recstrtpt_Iot=0;
            break;
       case 2: IoT_reccnt++;
               rec_arr_IoT[IoT_reccnt]=uartdata1;
               if(IoT_reccnt>=78)
               {
                    IoT_reccnt=0;uartdata1=0;
                    ucIOTSendFlag=1;
                    recstrtpt_Iot=0;
               }
           break;
       case 3: reccnt1++;
               rec_arr1[reccnt1]=uartdata1;
               if(reccnt1==12)
               {
                    reccnt1=0;recstrtpt_Iot=0;
                    ucSend_PSToRemote=1;
               }
           break;
       default:
           break;
   }
}

void __ISR(_ADC_VECTOR, IPL2SOFT) _ADC_Handler(void)
{
    result_AN2 = (ADC1BUF0+ADC1BUF2+ADC1BUF4+ADC1BUF6)/1;   
    result_AN3 = (ADC1BUF1+ADC1BUF3+ADC1BUF5+ADC1BUF7)/4;
    IFS1bits.AD1IF = 0; //   
    //adc_readf=1;
    //TRANS2('#');
}