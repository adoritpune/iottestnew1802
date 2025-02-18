//iot 

void storetomemory(unsigned char row_number_,unsigned char indexs)
{
    
	switch(row_number_)
	{
        
		//case '10':
		
		//iwirespeed = (((receive_ps_data[indexs]-0x30)*10)+(receive_ps_data[indexs+1]-0x30));
		//iwirespeed_higher=((receive_ps_data[indexs]-0x30)*10)+(receive_ps_data[indexs+1]-0x30);
		iwirespeed_higher=(iwirespeed_higher*10)+(receive_ps_data[indexs+2]-0x30);
		iwirespeed = (iwirespeed_higher*10)+(receive_ps_data[indexs+3]-0x30);
		
	    break;
		
		case 11:
            
		//added for testing
		isetcurrent_higher =((receive_ps_data[indexs]-0x30)*10)+(receive_ps_data[indexs+1]-0x30);
		isetcurrent_higher = (isetcurrent_higher*10)+(receive_ps_data[indexs+2]-0x30);
		isetcurrent = (isetcurrent_higher*10)+(receive_ps_data[indexs+3]-0x30);
		
		
	    break;
		
		case 12:
		isetvoltage_higher=((receive_ps_data[indexs]-0x30)*10)+(receive_ps_data[indexs+1]-0x30);
		isetvoltage_higher=(isetvoltage_higher*10)+(receive_ps_data[indexs+2]-0x30);
		isetvoltage=(isetvoltage_higher*10)+(receive_ps_data[indexs+3]-0x30);
		
		
		/*isetvoltage=receive_ps_data[indexs];
		isetvoltage=( ( isetvoltage<< 8 ) + receive_ps_data[indexs+1] );*/
		
		break;
		
		case 21:
           
		iactualcurrent_higer=((receive_ps_data[indexs]-0x30)*10)+(receive_ps_data[indexs+1]-0x30);
		iactualcurrent_higer=(iactualcurrent_higer*10)+(receive_ps_data[indexs+2]-0x30);
		iactualcurrent=(iactualcurrent_higer*10)+(receive_ps_data[indexs+3]-0x30);
		
		
		break;
		
		case 22:
		iactualvoltage_higher=((receive_ps_data[indexs]-0x30)*10)+(receive_ps_data[indexs+1]-0x30);
		iactualvoltage_higher=(iactualvoltage_higher*10)+(receive_ps_data[indexs+2]-0x30);
		iactualvoltage=(iactualvoltage_higher*10)+(receive_ps_data[indexs+3]-0x30);
		
		/*iactualvoltage=receive_ps_data[indexs];
		iactualvoltage=( ( iactualvoltage<< 8 ) + receive_ps_data[indexs+1] );*/
		//diswin1[2]=iactualvoltage;
        isetvoltage_test=71;
		break;
	  
	
        
		default:
            
		break;
			
	}




}

data_filter()
{
    
    //isetvoltage_test=43;
    
    if(received_datafrom_PS==0x0D && (OD_received_f==0 || OD_received_f==1) && response_f==0)
	   {
		   if(OD_received_f==0)
		   {
		    OD_received_f=1;
		   }
		   else if(OD_received_f==1)
		   {
		    OD_received_f=2;
		   
		   }
		   
	   }
	   else if(received_datafrom_PS==0x0A && (OD_received_f==1 || OD_received_f==2) && OD_OA_CHANGEOVER==0)//&& (response_started_f==0 || response_started_f==1))
	   {
	   
	           //TRANS2(0x40);
	           OD_received_f=0;
	           OD_OA_CHANGEOVER=1;
	           
	   }
	   
	   else if(OD_OA_CHANGEOVER==1 && received_datafrom_PS!=0x0D && received_datafrom_PS!=0x0A)// && start_f==0 && ok_f==0 && error_f==0 && response_f==0)
	   {
		   
		   
		   
		   if(received_datafrom_PS=='@')        //0X41)// && start_f==0)//A
		   {
               
			   new_row_f=1;
		   }
		   else if(new_row_f==1)
           {
                
                new_row_f=2;
                row_num_svd_f=0;
                row_number_h=received_datafrom_PS;
            
           
           }
           else if(new_row_f==2 && row_num_svd_f==0)
           {
                new_row_f=0;
                row_num_svd_f=1;
                

                //row_number=(row_number<<4)+received_datreafrom_PS;
                row_number=(row_number_h-0x30)*10+(received_datafrom_PS-0x30);
           
           }
           else if(row_num_svd_f==1)
           {
            
            if(received_datafrom_PS!='$')
            {
                
            receive_ps_data[position]=received_datafrom_PS;
            position++;
            }
            else
            {  
            position=0;
            //index=0;
            storetomemory(row_number,index);
            row_num_svd_f=0;
            OD_OA_CHANGEOVER=0;
            }
           }
		   
		   
	   }
    
}

void gprs_initialisation()
{  
   if(gprs_command_f==1 && command_sent=='X')
   {
		send_string_u1("AT+SAPBR=3,1,");  //B
		TRANS1(0x22); //"
		send_string_u1("CONTYPE");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x22); //"
		send_string_u1("GPRS");
		TRANS1(0x22);
		TRANS1(0x0D);
		TRANS1(0x0A);
		command_sent='B';
		gprs_command_f=0;
   }
   else if(gprs_command_f==1 && command_sent=='B')
   {
	   
	    send_string_u1("AT+SAPBR=3,1,");  //C
		TRANS1(0x22); //"
		send_string_u1("APN");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x22); //"
		send_string_u1("airtelgprs.com");
		TRANS1(0x22);
		TRANS1(0x0D);
		TRANS1(0x0A);
	    command_sent='C';
        gprs_command_f=0;
        //command_sent='B';
        
   }
   else if(gprs_command_f==1 && command_sent=='C')
   {
		send_string_u1("AT+SAPBR=1,1");   //D
		TRANS1(0x0D);
		TRANS1(0x0A);
		gprs_command_f=0;
		//ok_ff=0;
        command_sent='D';
   
   }
   else if(gprs_command_f==1 && command_sent=='D')
   {
		send_string_u1("AT+SAPBR=2,1");   //D
		TRANS1(0x0D);
		TRANS1(0x0A);
		gprs_command_f=0;
		//ok_ff=0;
        command_sent='L';
        
   }
   else if(gprs_command_f==1 && command_sent=='L')
   {
		send_string_u1("AT+CCLK?");   //D
		TRANS1(0x0D);
		TRANS1(0x0A);
		gprs_command_f=0;
		//ok_ff=0;
        command_sent='M';
        
   }
   else if(gprs_command_f==1 && command_sent=='M')
   {
		send_string_u1("AT+CLTS=1");   //D
		TRANS1(0x0D);
		TRANS1(0x0A);
		gprs_command_f=0;
		//ok_ff=0;
        command_sent='N';
        
   }
  /* else if(gprs_command_f==1 && command_sent=='R')
   {
		send_string_u1("AT+CLTS?");   //D
		TRANS1(0x0D);
		TRANS1(0x0A);
		gprs_command_f=0;
		//ok_ff=0;
        command_sent='N';
        
   }*/
   else if(gprs_command_f==1 && command_sent=='N')
   {
		send_string_u1("AT&W");   //D
		TRANS1(0x0D);
		TRANS1(0x0A);
		gprs_command_f=0;
		//ok_ff=0;
        command_sent='O';
        
   }
   else if(gprs_command_f==1 && command_sent=='O')
   {
		send_string_u1("AT+CCLK?");   //D
		TRANS1(0x0D);
		TRANS1(0x0A);
		gprs_command_f=0;
		//ok_ff=0;
        command_sent='E';
        
        
   }
   else if(gprs_command_f==1 && command_sent=='E')
   {
        
        send_string_u1("AT+HTTPINIT");
		TRANS1(0x0D);
		TRANS1(0x0A);
		command_sent='S';
		gprs_command_f=0;
   }
   	 
   else if(gprs_command_f==1 && command_sent=='S')
   {
        
        send_string_u1("AT+HTTPSSL=1");
		TRANS1(0x0D);
		TRANS1(0x0A);
		command_sent='A';
		gprs_command_f=0;
   } 
   else if(gprs_command_f==1 && command_sent=='A')
	{
		
		send_string_u1("AT+HTTPPARA=");
		TRANS1(0x22); //"
		send_string_u1("CID");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		send_string_u1("1");
		TRANS1(0x0D);
		TRANS1(0x0A);
		command_sent='F';
		gprs_command_f=0;
	}
	else if(gprs_command_f==1 && command_sent=='F')
	{
		
		send_string_u1("AT+HTTPPARA=");
		TRANS1(0x22); //"
		send_string_u1("URL");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x22); //"
		//send_string_u1("13.127.48.185:4100/api/DataLogger/SendMachineData");
		send_string_u1("14.143.203.76:4100/api/DataLogger/SendMachineData");//13.127.48.185:443
		TRANS1(0x22);
		TRANS1(0x0D);
		TRANS1(0x0A);
		command_sent='G';
		gprs_command_f=0;
	}

	else if(gprs_command_f==1 && command_sent=='G')
	{
		
		send_string_u1("AT+HTTPPARA=");
		TRANS1(0x22); //"
		send_string_u1("CONTENT");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x22); //"
		send_string_u1("application/json");
		//send_string_u1("multipart/form-data");
		TRANS1(0x22);
		TRANS1(0x0D);
		TRANS1(0x0A);
		command_sent='P'; //'H'
		gprs_command_f=0;
	}
    else if(gprs_command_f==1 && command_sent=='P')
   {
		send_string_u1("AT+CCLK?");   //D
		TRANS1(0x0D);
		TRANS1(0x0A);
		gprs_command_f=0;
		//ok_ff=0;
        command_sent='H';//H
        GSM_1sec=0;
        count_1min=0;
        GSM_Time_cmd=1;
        cRxreceiveONfg=1; //Added for to turn on RX2
   }
  /* else if(gprs_command_f==1 && command_sent=='R')//for location
   {
		send_string_u1("AT+CLBS=1,1");   //D
		TRANS1(0x0D);
		TRANS1(0x0A);
		gprs_command_f=0;
		//ok_ff=0;
        command_sent='H';
        
        
   }*/
	else if(gprs_command_f==1 && command_sent=='H' && Send_IOT_data==1)
	{
		
		send_string_u1("AT+HTTPDATA=1055,6000");//("AT+HTTPDATA=590,6000");    //6//9 sec
		TRANS1(0x0D);
		TRANS1(0x0A);
		command_sent='I';
		gprs_command_f=0;        
	}
	else if(gprs_command_f==1 && command_sent=='I')
	{
	
	    data_to_modem();
        //test_data_to_modem();
        //send_string_u2("IOT CNT = ");
        //TRANS2(IOTcnt);
	    gprs_command_f=0;
        Send_IOT_data=0;
       // ucnt=0;
       // tcnt=0;
       // IOTcnt=0;
	    command_sent='J';
	
	}
/*	else if(gprs_command_f==1 && command_sent=='S')
   {
        
        send_string_u1("AT+HTTPSSL=1");
		TRANS1(0x0D);
		TRANS1(0x0A);
		command_sent='J';
		gprs_command_f=0;
   }  */
	else if(gprs_command_f==1 && command_sent=='J')
	{
		send_string_u1("AT+HTTPACTION=1");
		TRANS1(0x0D);
		TRANS1(0x0A);
		gprs_command_f=0;
	    command_sent='K';
        readresponsef=1;
	    
	
	}
	else if(gprs_command_f==1 && command_sent=='K')
	{
		send_string_u1("AT+HTTPREAD");
		TRANS1(0x0D);
		TRANS1(0x0A);
		gprs_command_f=0;
        if(chk_RTC_time == 1)
        {
            command_sent='P';//'H';
            chk_RTC_time=0;
        }
        else
        {    
            command_sent='H';//'H';
        }
        //readresponsef=1;
        
	}
   
   


}
void data_to_modem()
{
	
	//if(0)
	{   ok_f=0;
	    TRANS1(0x7B); //{
		TRANS1(0x0D);
		TRANS1(0x0A);
		//json fields start here	
		TRANS1(0x22); //"
		send_string_u1("AuthKey");
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		
		TRANS1(0x22); //"
		send_string_u1("c3ltcGhvbnk=");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("MachineName");
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"           //45
        count=0;
        //while(count<15)
        while(count<machineName_cnt-1)    
        {
         TRANS1(cmodelname_arr[count]); 
          //TRANS1(cmodelnameR_arr[count]);  
         count++;
        }
		//send_string_u1("ChampPULSE 500");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("MachineID");
        //TRANS2('@');
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
        count=0;
        for(i=0;i<11;i++)//while(count<11)
        {
         TRANS1(cmachineidR_arr[i]); 
         //TRANS2(cmachineidR_arr[i]);
         //count++;
        }
		//send_string_u1("73/21126789"); //79/20210001//73/21126789// 73/211223445 // 73/21068753 
		TRANS1(0x22); //"
		TRANS1(0x2C); //, 
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("Software Revision");   //100
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
		count=0;
        while(count<3)
        {
         TRANS1(softrev_str[count]); 
         count++;
        }
        //send_string_u1("REV2.1");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("Command Number");
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
		send_string_u1("0");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("Xaxis");    //Latitude
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
		//send_string_u1("18.650952");   //18.65085
        //send_string_u2(" \nIOT  ");
        send_string_u2(" \nLatitude = ");
        count=0;
        if(default_locf==1)  //valid data from gps module
        {
            while(count<9)//8
            {
             //TRANS1(latdata[count]); 
             TRANS1(GPS_lat_buf[count]);
             TRANS2(GPS_lat_buf[count]); 
             count++;
            }
        }
        else
        {
            while(count<9)
            {
             TRANS1(default_lat[count]); 
             count++;
            }
        
        }
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("Yaxis");   //Longitude
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
		//send_string_u1("73.650952");  //073.78768
        send_string_u2(" \nLongitude = ");
        count=0;
        if(default_locf==1)  //valid data from gps module
        {
            while(count<10)//10
            {
             //TRANS1(longdata[count]);
             TRANS1(GPS_long_buf[count]);
             TRANS2(GPS_long_buf[count]);
             count++;
            }
        }
        else
        {
            while(count<10)
            {
             TRANS1(default_long[count]); 
             count++;
            }
        
        }
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("Process");
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
        count=0;
        while(count<13)//(twot_str[count]!='\0') //8
        {
           TRANS1(process_str[count]);
           count++;
        }
		//send_string_u1("MIG/MAG");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("WeldMode");
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
        count=0;
        while(count<2)//(twot_str[count]!='\0')
        {
           TRANS1(twot_str[count]);
           count++;
        }
		//send_string_u1("4T");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("Wire Speed");
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
		//send_string_u1("23.2");
		//send_value(iwirespeed);
		count=0;
        while(count<3)//(twot_str[count]!='\0')
        {
           TRANS1(Wirespeed_str[count]);
           count++;
        }	
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("SetCurrent");
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
		//send_string_u1("0165");
		//send_value(isetcurrent);
		count=0;
        while(count<4)//(twot_str[count]!='\0')
        {
           TRANS1(setcurrent_str[count]);
           count++;
        }		
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("SetVoltage");
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
		//send_string_u1("024.3");
		//send_value(isetvoltage);
		count=0;
        while(count<4)//(twot_str[count]!='\0')
        {
           TRANS1(setvoltage_str[count]);
           count++;
        }		
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("Metal");   //Material
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
        count=0;
        while(count<6)//(cmaterial_str[count]!='\0')
        {
           TRANS1(cmaterial_str[count]);
           count++;
        }
		//send_string_u1("MSFCAW");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("Diameter");
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
		count=0;
        while(count<3)//(twot_str[count]!='\0')
        {
           TRANS1(cdia_str1[count]); 
           count++;
        }
       // send_string_u1("1.2");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("Gas");
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
        count=0;
        while(count<12)//(cgas_str[count]!='\0')
        {
           TRANS1(cgas_str[count]);
           count++;
        }
		//send_string_u1("AR");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("HF");  //HF Status
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
		send_string_u1("OFF");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("Carriage");  //Carriage Status
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
		send_string_u1("OFF");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("Carriage Speed");
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
		send_string_u1("02.5");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("Time");
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
        send_string_u2(" \nTIME = ");
        //for(i = 0; i < 14; ++i)
        for(i = 0; i < 14; i++)    
        {
            TRANS1(cDateTimeArray[i]);
            TRANS2(cDateTimeArray[i]);
        }
		//send_string_u1("20220518095850");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("Welding");  //Status
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
        //send_string_u1("Weld ");
        //send_string_u2("\nWeld ");
		count=0;
        while(count<134)//(ctorch_status[count]!='\0')
        {
           TRANS1(ctorch_status[count]);
           //TRANS2(ctorch_status[count]);
           count++;
        }
      /*  if(weld_on_f==1)//(weldon_off == 1 )
        {
           send_string_u1("ON");
          // send_string_u2("ON");
        } 
        else// if(weldon_off == 2 )
        {
           send_string_u1("OFF"); 
          // send_string_u2("OFF"); 
           lastcurrentf=0;
           //lastcurrent1f=0;
        } */
        
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("ActualCurrent");
        //send_string_u2("ActualCurrent");
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
		//send_string_u1("176");
		//send_value(iactualcurrent);
        //send_value_2(iactualcurrent);
        count=0;
        while(count<74)
        {
           TRANS1(cAcualcur_Tx[count]); 
           count++;
        
        }
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("ActualVoltage");
        //send_string_u2("ActualVoltage");
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
		//send_string_u1("21.5");
		//send_value(iactualvoltage);
        //send_value_2(iactualvoltage);
        count=0;
        while(count<74)
        {
           TRANS1(cActualvtg_Tx[count]); 
           count++;
        
        }
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("Error");
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
        switch(error_str[2])
        {
            case '1':
                send_string_u1("Under Voltage");
                break;
            case '2':
                send_string_u1("Over Voltage");
                break;
            case '3':
                send_string_u1("Thermal Error");
                break;
            case '4':
                send_string_u1("No Current");
                break;
            case '5':
                send_string_u1("Motor Overload");
                break;
            case '7':
                send_string_u1("Pressure Error");
                break;
            case '8':
                send_string_u1("Communication error");
                break;
            default:
                send_string_u1("No Error");
                break;
        
        
        }
		//send_string_u1("No Error");
		TRANS1(0x22); //"
		TRANS1(0x2C); //,
		TRANS1(0x0D);
		TRANS1(0x0A);
		
		TRANS1(0x22); //"
		send_string_u1("ARCONTIME");
		TRANS1(0x22); //"
		TRANS1(0x3A); //:
		TRANS1(0x22); //"
		//send_string_u1("18:34");
        count=0;
        while(count<3)
        {
           TRANS1(arcontime_str[count]); 
           count++;
        
        }
		TRANS1(0x22); //"
		
		
		TRANS1(0x0D);
		TRANS1(0x0A);
		TRANS1(0x7D); //}
		
		
	}	
		

}

void test_data_to_modem()
{
	
	//if(0)
	{   ok_f=0;
	    TRANS2(0x7B); //{
		TRANS2(0x0D);
		TRANS2(0x0A);
		//json fields start here	
		TRANS2(0x22); //"
		send_string_u2("AuthKey");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		
		TRANS2(0x22); //"
		send_string_u2("c3ltcGhvbnk=");
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
		TRANS2(0x22); //"
		send_string_u2("MachineName");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"           //45
        count=0;
        //while(count<15)
        while(count<machineName_cnt-1)    
        {
         TRANS2(cmodelname_arr[count]); 
          //TRANS1(cmodelnameR_arr[count]);  
         count++;
        }
		//send_string_u1("ChampPULSE 500");
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
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
		//send_string_u1("73/21126789"); //79/20210001//73/21126789// 73/211223445 // 73/21068753 
		TRANS2(0x22); //"
		TRANS2(0x2C); //, 
		TRANS2(0x0D);
		TRANS2(0x0A);
		
		TRANS2(0x22); //"
		send_string_u2("Software Revision");   //100
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		count=0;
        while(count<3)
        {
         TRANS2(softrev_str[count]); 
         count++;
        }
        //send_string_u1("REV2.1");
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
		TRANS2(0x22); //"
		send_string_u2("Command Number");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		send_string_u2("0");
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
		TRANS2(0x22); //"
		send_string_u2("Xaxis");    //Latitude
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		//send_string_u1("18.650952");   //18.65085
        //send_string_u2(" \nIOT  ");
        //send_string_u2(" \nLatitude = ");
        count=0;
        if(default_locf==1)  //valid data from gps module
        {
            while(count<9)//8
            {
             //TRANS1(latdata[count]); 
             //TRANS1(GPS_lat_buf[count]);
             TRANS2(GPS_lat_buf[count]); 
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
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
		TRANS2(0x22); //"
		send_string_u2("Yaxis");   //Longitude
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		//send_string_u1("73.650952");  //073.78768
        //send_string_u2(" \nLongitude = ");
        count=0;
        if(default_locf==1)  //valid data from gps module
        {
            while(count<10)//10
            {
             //TRANS1(longdata[count]);
            // TRANS1(GPS_long_buf[count]);
             TRANS2(GPS_long_buf[count]);
             count++;
            }
        }
        else
        {
            while(count<10)
            {
             TRANS2(default_long[count]); 
             count++;
            }
        
        }
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
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
		//send_string_u1("MIG/MAG");
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
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
		//send_string_u1("4T");
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
		TRANS2(0x22); //"
		send_string_u2("Wire Speed");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		//send_string_u1("23.2");
		//send_value_2(iwirespeed);
		count=0;
        while(count<3)//(twot_str[count]!='\0')
        {
           TRANS2(Wirespeed_str[count]);
           count++;
        }		
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
		TRANS2(0x22); //"
		send_string_u2("SetCurrent");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		//send_string_u1("0165");
		//send_value_2(isetcurrent);
		count=0;
        while(count<4)//(twot_str[count]!='\0')
        {
           TRANS2(setcurrent_str[count]);
           count++;
        }		
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
		TRANS2(0x22); //"
		send_string_u2("SetVoltage");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		//send_string_u1("024.3");
		//send_value_2(isetvoltage);
		count=0;
        while(count<4)//(twot_str[count]!='\0')
        {
           TRANS2(setvoltage_str[count]);
           count++;
        }		
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
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
		//send_string_u1("MSFCAW");
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
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
       // send_string_u1("1.2");
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
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
		//send_string_u1("AR");
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
		TRANS2(0x22); //"
		send_string_u2("HF");  //HF Status
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		send_string_u2("OFF");
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
		TRANS2(0x22); //"
		send_string_u2("Carriage");  //Carriage Status
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		send_string_u2("OFF");
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
		TRANS2(0x22); //"
		send_string_u2("Carriage Speed");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		send_string_u2("02.5");
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
		TRANS2(0x22); //"
		send_string_u2("Time");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
        //send_string_u2(" \nTIME = ");
        //for(i = 0; i < 14; ++i)
        for(i = 0; i < 14; i++)    
        {
            //TRANS1(cDateTimeArray[i]);
            TRANS2(cDateTimeArray[i]);
        }
		//send_string_u1("20220518095850");
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
		TRANS2(0x22); //"
		send_string_u2("Welding");  //Status
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
        //send_string_u2("Weld ");
        //send_string_u2("\nWeld ");
		count=0;
        while(count<134)//(ctorch_status[count]!='\0')
        {
           TRANS2(ctorch_status[count]);
           //TRANS2(ctorch_status[count]);
           count++;
        }
      /*  if(weld_on_f==1)//(weldon_off == 1 )
        {
           send_string_u1("ON");
          // send_string_u2("ON");
        } 
        else// if(weldon_off == 2 )
        {
           send_string_u1("OFF"); 
          // send_string_u2("OFF"); 
           lastcurrentf=0;
           //lastcurrent1f=0;
        } */
        
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
		TRANS2(0x22); //"
		send_string_u2("ActualCurrent");
        //send_string_u2("ActualCurrent");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		//send_string_u1("176");
		//send_value(iactualcurrent);
       // send_value_2(iactualcurrent);
        count=0;
        while(count<74)
        {
           TRANS2(cAcualcur_Tx[count]); 
           count++;
        
        }
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
		TRANS2(0x22); //"
		send_string_u2("ActualVoltage");
        //send_string_u2("ActualVoltage");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
		//send_string_u1("21.5");
		//send_value(iactualvoltage);
        //send_value_2(iactualvoltage);
        count=0;
        while(count<74)
        {
           TRANS2(cActualvtg_Tx[count]); 
           count++;
        
        }
		TRANS2(0x22); //"
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
		TRANS2(0x22); //"
		send_string_u2("Error");
		TRANS2(0x22); //"
		TRANS2(0x3A); //:
		TRANS2(0x22); //"
        TRANS2(error_str[2]); //"
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
		TRANS2(0x2C); //,
		TRANS2(0x0D);
		TRANS2(0x0A);
		
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
		TRANS2(0x0A);
		TRANS2(0x7D); //}
		
		
	}	
		

}
/*void decode_psdata()
{
  //PORTAINV=0X0040;
  position=0;             //array position zero decoding starts
  for(index=0;index<60;index++)
  {   
	  if(receive_ps_data[index]=='@' && crlf_f==1)
	  {   iactualcurrent=25;
		  crlf_f=0;
		  new_row_f=1;
	  }
	  else if(new_row_f==1)
	  {
		  new_row_f=0;
		  row_num_svd_f=1;
		  row_number=receive_ps_data[index];
		  row_number=(row_number<<4)+receive_ps_data[index+1];
	  }
	  else if(row_num_svd_f==1)
	  {
          
		  storetomemory(row_number,(index+1));
	      row_num_svd_f=0;
	  }
	  else if(receive_ps_data[index]=='$')   //THIS CAN BE DONE IN storetomemory function, to save time
	  {
		  
	      crlf_f=1;
	      //row_number=0;
	      //diswin1[2]=row_number;
		  //diswin1[1]=action_arr[15];
          //diswin1[0]=action_arr[14];
	  
	  }
  
  }
	
}
*/