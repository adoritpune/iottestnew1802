void Wifi_initialisation()
{
    switch(ATcommand)  // AT+RST
    {
        
        case 0:if(send_ATcmdFlag==0)
                {
                    send_string_u4("AT+RST");              
                    TRANS4(0x0D);
                    TRANS4(0x0A);
                    send_ATcmdFlag=1;count_5min=0;
                } 
                if(ucWiFiOk==1)
                {
                    ATcommand=1;send_ATcmdFlag=0;count_5min=0; ucWiFiOk=0;
                }
                break; 
        case 1:if(send_ATcmdFlag==0)
                {
                    send_string_u4("AT");              
                    TRANS4(0x0D);
                    TRANS4(0x0A);
                    send_ATcmdFlag=1;count_5min=0;
                } 
                if(ucWiFiOk==1)
                {
                    ATcommand=2;send_ATcmdFlag=0;count_5min=0; ucWiFiOk=0;
                }
                break;  
        case 2: if(send_ATcmdFlag==0)
                {
                    send_ATcmd=0;  
                    send_string_u4("AT+CWMODE=1");
                    TRANS4(0x0D);
                    TRANS4(0x0A);
                    send_ATcmdFlag=1;
                } 
               if(ucWiFiOk==1)
                {
                    ATcommand=3;send_ATcmdFlag=0;count_5min=0; ucWiFiOk=0;
                }
                break;    
        case 3: if(send_ATcmdFlag==0)
                {
                    send_string_u4("AT+CWJAP=\"Ketan\",\"ketan@4895\"");             
                    TRANS4(0x0D);
                    TRANS4(0x0A);
                    send_ATcmdFlag=1;
                } 
                if(ucWiFiOk==1)
                {
                    ATcommand=4;send_ATcmdFlag=0;count_5min=0; ucWiFiOk=0;
                }
                break;
        case 4: if(send_ATcmdFlag==0)
                {
                    send_string_u4("AT+CIPMODE=0");   
                    TRANS4(0x0D);
                    TRANS4(0x0A);  
                    send_ATcmdFlag=1;
                } 
               if(ucWiFiOk==1)
                {
                    ATcommand=5;send_ATcmdFlag=0;count_5min=0; ucWiFiOk=0;
                }
                break;  
        case 5: if(send_ATcmdFlag==0)
                {  
                    send_string_u4("AT+CIPMUX=1");  
                    TRANS4(0x0D);
                    TRANS4(0x0A);
                    send_ATcmdFlag=1; 
                } 
                if(ucWiFiOk==1)
                {
                    //ATcommand=6;send_ATcmdFlag=0;count_5min=0; ucWiFiOk=0;
                    ATcommand=10;send_ATcmdFlag=0;count_5min=0; ucWiFiOk=0;power_ON_delay_f=0;WifiSend=1;
                }
                break;   
        case 6: if(send_ATcmdFlag==0)
                { 
                    send_string_u4("AT+CIPSERVER=1,80");  
                    TRANS4(0x0D);
                    TRANS4(0x0A); 
                    send_ATcmdFlag=1;
                } 
                if(ucWiFiOk==1)
                {
                 //   ATcommand=10;send_ATcmdFlag=0;count_5min=0; ucWiFiOk=0;power_ON_delay_f=0;WifiSend=1;
                }
                break;
                
        default:
                break;
    } 
}
              
              
void Wifi_Send_Data(void)
{
   switch(WifiSend)
   {
        case 1: if(send_ATcmdFlag==0)
                {        
                    send_string_u4("AT+CIPSERVER=1,80");  
                    TRANS4(0x0D);
                    TRANS4(0x0A);
                    send_ATcmdFlag=1;
                }
                if(ucWiFiOk==1)
                {
                    WifiSend=2;send_ATcmdFlag=0;count_5min=0; ucWiFiOk=0;
                }
                break;
         case 2: if(send_ATcmdFlag==0)
                {        
                    send_string_u4("AT+CIPSEND=0,20");   
                    TRANS4(0x0D);
                    TRANS4(0x0A);
                    send_ATcmdFlag=1;
                }
                if(ucWiFiOk==1)
                {
                    WifiSend=3;send_ATcmdFlag=0;count_5min=0; ucWiFiOk=0;
                }
                break;
        case 3: if(send_ATcmdFlag==0)
                {  
                    TRANS4('V');TRANS4(':');
                    send_value(SetVoltage);
                    TRANS4('C');TRANS4(':');
                    send_value(SetCurrent);
                    TRANS4('W');TRANS4(':');
                    send_value(SetWiSpeed);
                    TRANS4(0x0D);
                    TRANS4(0x0A);
                    send_ATcmdFlag=1;
                } 
                if(ucWiFiOk==1)
                {
                    WifiSend=1;send_ATcmdFlag=0;count_5min=0; ucWiFiOk=0;
                }
                break; 
       default:
           break;
   }
}