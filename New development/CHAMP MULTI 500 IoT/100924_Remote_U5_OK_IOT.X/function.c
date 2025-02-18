//function prototypes
void system_initialise();
void oscillator_init();
void gpio_init();
void uart1_init();
void uart2_init();
void uart4_init();
void uart5_init();
void timer1_init();
void timer2_init();
void trans_uart2(unsigned int);
void TRANS5(unsigned char);
void TRANS2(unsigned char);
void TRANS4(unsigned char);
void TRANS1(unsigned char data);
void send_AT();

void send_string_u1(char *s);
void send_string_u2(char *s);
void send_string_u4(char *s);
void send_string_u5(char *s);
void transmit_to_modem();
void data_to_modem();
void gprs_initialisation();
void decode_psdata();             //@iot
void storetomemory(unsigned char,unsigned char);//@iot
void data_filter();               //@iot
void send_value(unsigned int);
void send_value_2(unsigned int);
void send_value_string(unsigned char*);
//void delayI2C();

void i2cinit();
void startBitGen();
void stopBitGen();
void I2C_Write1(unsigned int, unsigned char);      // unsigned char);
void I2C_Write2(unsigned int, unsigned char, unsigned char); 
unsigned int I2C_Read1(unsigned int, unsigned char);
unsigned int I2C_Read(unsigned int, unsigned char, unsigned char*);
void RTC_Read();
void bytewrite(unsigned char);
void bytewrite_rtc(unsigned char);
unsigned char byteread();
void ACK();
void ACK_RTC();
void NOACK();
void delayI2C();
void clock_simu();
void RTC_Write();
void ADC_init();
unsigned char Model_select();
void ADC_Read();
void RTC_Write_Test();
void bytewrite_rtc_Test(short int data);
unsigned char DATE_TIME(unsigned char , unsigned char );
void ReadMachine_details();
void DecimalDegrees(const char *latLon,char quadrant,unsigned char latlonsel);
void DisplayJasonLineOnTerminal(unsigned int cLineNo);
void Wifi_initialisation();
void clearVAL();
void send_value_4(unsigned int value);
void data_to_Wifi();
void Append_data_analog();
void Int_to_ascii(unsigned int );
void test_data_to_modem();
void Append_data_digital();						   
