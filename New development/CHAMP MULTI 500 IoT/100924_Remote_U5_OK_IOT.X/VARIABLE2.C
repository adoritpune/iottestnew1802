unsigned char cmachineid_arr[200],cmachineidR_arr[16];

unsigned char ci,cone_sec,chalf_sec,cfive_sec,cmodem_data_gps=0,cmodem_data1=0,cmodem_data2=0,fifty_sec_flag,cstart_data_filter;
unsigned int ione_sec_count,ihalf_sec_count,ifive_sec_count,data=0x67,RX_data=0,RX_data4=0,fifty_sec,idelay;
unsigned char cdollar_f,cfirstg_f,cfirstp_f,cfirstl_f,len=0,j;
//gps_data[20],gps_data_saved[20]

unsigned int itest,jj=0,i,power_ON_delay=0,power_ON_delay_f=0;
unsigned char new_json_f=0,read_bytes_f=0,position=0,decode_psdata_f=0,decode_delay_f=0,decode_Delay=0,temp,
row_num_svd_f=0,row_number=0,row_number_h=0,crlf_f=0,new_row_f=0,index1=0,index=0;row_number_=0,indexs=0,str_counter=0;//cdata_saved_f=0;
unsigned char cmaterial_str[8],ctorch_status[135],ctorch_status_mc[4]={'O','F','F'},
        twot_str[4],receive_ps_data[4], cdia_str1[4],
        softrev_str[8], error_str[4]={0}, arcontime_str[8];
//unsigned char cgas_str[16]="ARCO2(98+02)";
unsigned char received_datafrom_PS=0,digital_commf=0,received_data_TEST=0;



//unsigned char cmachineid_arr[11]="73/21073245",cmodelname_arr[15]="CHAMP PULSE 500"

unsigned char cmodelname_arr[15]="CHAMPPULSE 500",
        cmodelnameR_arr[15],cDateTimeArray[15],cE2pArray[5];

//rtc_arr[8], rtcR_arr[8], celement[],

unsigned char count,count1,check_statusf,iv,commas,default_locf=0;
unsigned char memory_check=0x43,terminaldataf,num,idreceivedf,mdlreceivedf,mdlwritef,idwritef; 
//unsigned char default_lat[8]="1865.085", default_long[8]="07378.76";//ADOR
//unsigned char default_lat[8]="1839.089", default_long[8]="07347.37";
//unsigned char default_lat[8]="1911.047", default_long[8]="07467.26";//AHMEDNAGAR
//unsigned char default_lat[8]="1817.899", default_long[8]="07455.53"; //BARAMATI

//unsigned char default_lat[8], default_long[8];

//IoT start
unsigned char terminal_in=0,A_RECEIVED_F=0,T_RECEIVED_F=0,O_RECEIVED_F=0,K_RECEIVED_F=0,COMMAND_NUM=0,COMMAND_NUM_TX=0;
unsigned char OD_received_f=0,E_RECEIVED_F=0,READ_START_F=0,response_started_f=0,OD_OA_CHANGEOVER=0,check_status_f=0,start_f=0,
ok_f=0,error_f=0,response_f=0,ok_ff=0;
//
unsigned char json_msg_f=0,uart_data_f=0,in_json_f=0,action_arr[40],transmit_to_modem_rdy=0,
power_on_tx=0,onesec_data=0,send_j=0,modem_response_f=0,command_sent='X',gprs_command_f=0,weld_on_off_f=0;
unsigned int arr_pointer=0,U1_rxdata_tx[],arr_pointer1=0,transmit_modem=0,tx_one_sec=0,gprs_command_cnt=0,weld_on_off=0;
unsigned int value=0,isetcurrent_higher=0,isetcurrent_lower=0,isetvoltage_higher=0,iactualcurrent_higer=0,iactualvoltage_higher=0,
iwirespeed_higher=0,isetvoltage_test;
unsigned char byteno,count_6ms,ij,j,readresponsef;
unsigned char str1[]={0x32,0x30,0x30}, str2[],Rstr1[],Rstr2[],str_startf,str_endf,strcmp_res=1;

//gps
unsigned char latfinishf,longfinishf,longdata[10],latdata[10];
unsigned char default_lat[9]="1839.0777", default_long[10]="07347.3309";
//storage buffers
unsigned char cgas_str[16]="ARCO2(98+02)",process_str[14]="PULSEMIG MODE",count_5min1=0,weldon_off=1,count_5sec;
unsigned char weld_on_f=0,MachineId_writef=0,machineId_cnt=0,high_byte=0,low_byte=0,adcflag=0,machineName_cnt=0;
unsigned char readDollorf=0,machineI_arr[16],machineI_cnt=0,MachineName_writef=0,MachineI_writef=0,max_current_arr[5];
unsigned char machineIR_arr[16],Machine_Model=0;
unsigned int  count_5min=0,adc_readf=0;

unsigned int  AN2_ADCValue=0,AN3_ADCValue=0,result_AN2=0,result_AN3=0,adc_cnt=0,adccurrent=0,adcvoltage=0; 
float         maxshunt = 6.0,slope = 9.30;

unsigned char GPS_arr[100],testflag=0,indx=0,tempcount=0,gsmtimef=0,GSM_time_arr[20],cnt=0,gsmdata=0,gsmtimef_1=0;
//short int Hr=0,Min=0,Sec=0,Year=0,Month=0,Day=0;
unsigned char tempf=0,Hr=0,Min=0,Sec=0,Year=0,Month=0,Day=0;
unsigned char GSM_1sec=0,GSM_Time_cmd=0,tempv=0,RTC_Min=0,time_result=0,GSM_modemf=0,count_60min=0,chk_RTC_time=0;
unsigned int  GSM_time=0,count_1min=0,preadccurrent=0,preadcvoltage=0; 
unsigned char gpsflag=0,GPScnt=0,RTC_time=0,testflag1=0;
unsigned char RTC_Year=0,RTC_Month=0,RTC_Day=0;

unsigned char lat_arr[9], long_arr[10],default_loct[20],Defaultloc_writef=0,writetoepromf=0,firsttimef=0,gpstestflag=0;
unsigned char lastcurrentf=0,lastcurrent1f=0;
unsigned int  testcnt=0;
unsigned char GPS_loc_recvf=0,sign=0; 
unsigned char default_lat1[9]="1839.0355", default_long1[10]="07347.3536",GPS_lat_buf[9],GPS_long_buf[10];
//double latitude1,longitude1;

//default_lat1[9]="0037.0852" "1839.0355", default_long1[10]="07313.498""07347.3536"
unsigned int iCount_1Sec,iValidGPSLocCNTR,count_20sec=0;
unsigned char cRB15level,cValidGPSLocFG,Pwron_delay_adc=0;
unsigned char transtowifi,cdatafrom_Wifi,cWifidata_recvf,fisttimesend,send_ATcmd=0,Wifi_arr[100],val=0,cWifi_Responsef=0;
unsigned char cWifi_dataf=0,cWificnt=0;


unsigned char wifiGET[]="GET http://14.143.203.76:4100/api/DataLogger/GetStatusOfAPI HTTP/1.1\r\nHost: 14.143.203.76:4100\r\n\r\n";
unsigned int  wifistrlen;
unsigned char cWifistrlen;
unsigned char wifiPOST[]="POST /api/DataLogger/SendMachineData HTTP/1.1\r\nHost: 14.143.203.76\r\nConnection: keep-alive\r\nContent-Type: application/json\r\nContent-Length: 640\r\n\r\n";
//unsigned char cWifidata[]="{\r\n    \"AuthKey\":\"c3ltcGhvbnk=\",\r\n    \"MachineName\":\"ChampPulse 500\",\r\n    \"MachineID\":\"73/21126789\",\r\n    \"Software Revision\":\"Rev2.1\",\r\n    \"Command Number\":\"1\",\r\n    \"Xaxis\":\"18.650952\",\r\n    \"Yaxis\":\"73.789293\",\r\n    \"Process\":\"MAG/MIG\",\r\n    \"WeldMode\":\"2T\",\r\n    \"Wire Speed\":\"25.0\",\r\n    \"SetCurrent\":\"0100\",\r\n    \"SetVoltage\":\"019.3\",\r\n    \"Metal\":\"MSFCAW.....\",\r\n    \"Diameter\":\"1.2\",\r\n    \"HF\":\"ON\",\r\n    \"Carriage\":\"ON\",\r\n    \"Carriage Speed\":\"02.5\",\r\n    \"Time\":\"20220523150359\",\r\n    \"Welding\":\"Weld OFF\",\r\n    \"ActualCurrent\":\"120\",\r\n    \"ActualVoltage\":\"19.6\",\r\n    \"Error\":\"Over Voltage Error\",\r\n    \"ARCONTIME\":\"12:34\"\r\n}\r\n";
unsigned char cWifidata[]="{\r\n    \"AuthKey\":\"c3ltcGhvbnk=\",\r\n    \"MachineName\":\"ChampPulse 500\",\r\n    \"MachineID\":\"79/21027777\",\r\n    \"Software Revision\":\"Rev2.1\",\r\n    \"Command Number\":\"1\",\r\n    \"Xaxis\":\"18.650952\",\r\n    \"Yaxis\":\"73.789293\",\r\n    \"Process\":\"MAG/MIG\",\r\n    \"WeldMode\":\"2T\",\r\n    \"Wire Speed\":\"25.0\",\r\n    \"SetCurrent\":\"0100\",\r\n    \"SetVoltage\":\"019.3\",\r\n    \"Metal\":\"MSFCAW.....\",\r\n    \"Diameter\":\"1.2\",\r\n    \"HF\":\"ON\",\r\n    \"Carriage\":\"ON\",\r\n    \"Carriage Speed\":\"02.5\",\r\n    \"Time\":\"20220523160259\",\r\n    \"Welding\":\"Weld OFF\",\r\n    \"ActualCurrent\":\"120\",\r\n    \"ActualVoltage\":\"19.6\",\r\n    \"Error\":\"Over Voltage Error\",\r\n    \"ARCONTIME\":\"12:34\"\r\n}\r\n";

unsigned char cAcualcur[80],cActualvtg[80],cWeld_status[135]={'O','F','F'},temp_arr[4];
unsigned char high=0, low=0,middle=0,highest=0,ucnt=0,tcnt=0,cCount_15Sec=0;
unsigned int  tempvalue=0,Send_IOT_data=0,Copy_IOT_data,data_wifi=0;
unsigned char IOTcnt=0,cAcualcur_Tx[80],cActualvtg_Tx[80],received_data[10];
unsigned char Wirespeed_str[4],setcurrent_str[4],setvoltage_str[4],ActCurrent_str[4],ActVoltage_str[4];
unsigned char conetimewf=0,cRxreceiveONfg=0,cRXenablefg=0;				


unsigned char Wifi_response=0,ATcommand=0,send_ATcmdFlag=0,ucWiFiOk=0,transchksum=0,recchksum=0,transon=1,receivef=0,uartdata=0,uartdata1=0,recstrtptr=0,reccnt=0,reccnt1=0,sendtoremotef=0,recstrtptr1=0;
unsigned int rec_arr[6]={0};
unsigned int rec_arr1[14]={0};
unsigned int k=0,sendvtg=0,sendcur=0,dummy1=0,dummy2=0,pwmtime1=0,weldcurrent=0,SetVoltage=0;
unsigned int SetCurrent=0,SetWiSpeed=0;
unsigned char Wifidata[10];
unsigned char model=0,errflag1='N',errflag2='N',ucSend_RemoteToPS=0,ucSend_PSToRemote=0,WifiSend=0;