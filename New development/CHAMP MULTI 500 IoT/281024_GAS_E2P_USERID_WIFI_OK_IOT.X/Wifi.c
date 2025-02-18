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
                    send_string_u4("AT");       //AT+PING="IP"       
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
                    //send_string_u4("AT+CWJAP=\"admin\",\"ador@123\"");  //Ador_CHI awlpune@         admin  ador@123
                    send_string_u4("AT+CWJAP=");
                    TRANS4(0x22); // "
                    for(i=0;i<5;i++) //  5
                    {
                        TRANS4(ucRxPass[i]);
                    }
                    TRANS4(0x22);// "
                    TRANS4(0x2C);// ,
                    TRANS4(0x22);
                    for(i=6;i<14;i++) //  6-14  4-16
                    {
                        TRANS4(ucRxPass[i]);
                    }
                    TRANS4(0x22);
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
                    send_string_u4("AT+CIPMODE=0");  // 
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
                    send_string_u4("AT+CIPSERVER=1,5210");  //80  443 5210
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
                    if(ucIOTcheck==0)
                    {
                        ucIOTcheck=1;
                        TRANS5('#');
                    }
                  //  if(ucIOTSendFlag==1)
                    {
                        send_string_u4("AT+CIPSERVER=1,5210");  //80:ok  443:ok 5210:ok
                        TRANS4(0x0D);
                        TRANS4(0x0A);
                    }
                    send_ATcmdFlag=1;
                }
                if(ucWiFiOk==1)
                {
                    WifiSend=2;send_ATcmdFlag=0;count_5min=0; ucWiFiOk=0;
                }
                break;
         case 2: if(send_ATcmdFlag==0)
                {    
                    if((ucIOTSendFlag==1)&&(ucPass==0))
                    {
                        send_string_u4("AT+CIPSEND=0,84");  //55  //83
                        TRANS4(0x0D);
                        TRANS4(0x0A);
                    }
                   
                    if(ucPass==1)
                    {
                        send_string_u4("AT+CIPSEND=0,");
                        send_valueID(ucPIndex);                      
                        TRANS4(0x0D);
                        TRANS4(0x0A);
                    }
                    send_ATcmdFlag=1; 
                }
                if(ucWiFiOk==1)
                {
                    WifiSend=3;send_ATcmdFlag=0;count_5min=0; ucWiFiOk=0;
                    ucIOTcheck=0;
                }
                break;
        case 3: if(send_ATcmdFlag==0)
                {  
                    //TRANS4('K');TRANS4(':');
                    //send_value(result_AN2);
                    //send_value(Gas_result);
                    if(ucPass==0)
                    {
                        if(ucIOTSendFlag==1)
                        {
                         ucIOTSendFlag=0;
                         for(i=0;i<78;i++)
                            TRANS4(rec_arr_IoT[i]);
                        }
                        TRANS4('K');TRANS4(':');
                        send_value(Gas_result); 
                    }
                    if(ucPass==1)
                    {
                        ucPass=0;
                        WIFIRST=1;
                        for(i=0;i<ucPIndex;i++)
                            TRANS4(ucRxPass[i]);                    
                        I2C_Write1(INDEX_ID_ADDR,ucPIndex);
                        E2PWrite(USER_ID_ADDR,(ucPIndex+1),ucRxPass);                    
                    }
                    TRANS4(0x0D);
                    TRANS4(0x0A);
                    send_ATcmdFlag=1;   
                } 
                if(ucWiFiOk==1 && WIFIRST==1)
                {
                    WifiSend=0;send_ATcmdFlag=0;count_5min=0; ucWiFiOk=0;
                    ucIOTcheck=0;
                    WIFIRST=0;
                    ATcommand=0;
                    power_ON_delay_f=1;
                }
                else if(ucWiFiOk==1)
                {
                    WifiSend=1;send_ATcmdFlag=0;count_5min=0; ucWiFiOk=0;
                    ucIOTcheck=0;  
                }
                break; 
       default:
           break;
   }
}

void IOT_control_send_data(void)
{
    switch(IOT_control)
    {
        case 1:
                send_string_u5("?QP"); 
                TRANS5(ucPROG);
                IOT_control=0; 
               break;
        case 2:send_string_u5("?QW"); 
               for(i=0;i<3;i++)    
                 TRANS5(ucWS[i]);
                IOT_control=0; 
               break;
        case 3:send_string_u5("?QV"); 
               for(i=0;i<3;i++)    
                 TRANS5(ucSetV[i]);
                IOT_control=0; 
               break;  
        case 4:
                send_string_u5("?QD"); 
                TRANS5(ucWireDiameter);
                IOT_control=0; 
               break;
        case 5:
                send_string_u5("?QM"); 
                TRANS5(ucMode);
                IOT_control=0; 
               break;
        case 6:
                send_string_u5("?QC"); 
                TRANS5(ucMaterial);
                IOT_control=0; 
               break;
        case 7:
                send_string_u5("?QG"); 
                TRANS5(ucGas);
                IOT_control=0; 
               break;
        case 8:
                send_string_u5("?QA"); 
                TRANS5(ucAuto_MANUAL);
                IOT_control=0; 
               break;
        case 9:send_string_u5("?QI"); 
               for(i=0;i<3;i++)    
                 TRANS5(ucMMA_Current[i]);
                IOT_control=0; 
               break; 
        case 10:send_string_u5("?QF"); 
               for(i=0;i<3;i++)    
                 TRANS5(ucArc_Force[i]);
                IOT_control=0; 
               break; 
        case 11:
                send_string_u5("?QR"); 
                TRANS5(ucArcForceON_OFF);
                IOT_control=0; 
               break;
        case 12:send_string_u5("?QT"); 
               for(i=0;i<3;i++)    
                 TRANS5(ucTIG_Current[i]);
                IOT_control=0; 
               break; 
        case 13:send_string_u5("?QL"); 
               for(i=0;i<3;i++)    
                 TRANS5(ucPassword[i]);
                IOT_control=0; 
               break; 
        case 14:
                send_string_u5("?QY"); 
                TRANS5(ucLockDisable);
                IOT_control=0; 
               break;
        case 15:send_string_u5("?QJ"); 
               for(i=0;i<2;i++)    
                 TRANS5(ucSJ[i]);
                IOT_control=0; 
               break; 
        case 16:send_string_u5("?QX"); 
               for(i=0;i<2;i++)    
                 TRANS5(ucRJ[i]);
                IOT_control=0; 
               break; 
        default: 
            break;
    }   
}


void GASFLOW_MEASURMENT(void)
{
    Gas_result=result_AN2;
    Gas_result=Gas_result*0.8067;    //Vres=5/4095=1.22mV
}