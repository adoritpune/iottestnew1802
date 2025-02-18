void system_initialise()
{
    oscillator_init();
    gpio_init();
    timer1_init();
    timer2_init();
    uart1_init();
    uart2_init();
    uart4_init();
    uart5_init();
    //ADC_init();
    
    
   // RESET=1;
    /*INTCONCLR=0X00000700;
    IPTMRCLR=0XFFFFFFFF;
    INTCONSET=0X00000700;
    IPTMR=0X12345678;*/
    
}
void oscillator_init()
{
    OSCCONbits.COSC=0x01;       //internal fast RC oscillator(8MHZ) with PLL module via post scaler is selected
    OSCTUNbits.TUN=0x00;        //oscillator runs at nominal frequency 8MHZ
    OSCCONbits.FRCDIV=0x01;     //FRC divided by 2 default setting  ->4MHZ
    OSCCONbits.PLLODIV=0x01;    //divide by 2    ->2MHZ 
    OSCCONbits.PLLMULT=0x07;    //multiply by 24  ->48MHZ
    
    OSCCONbits.PBDIV=0x00;      //peripheral clock is sys clock
    OSCCONbits.SOSCRDY=0;       //secondary osc turned off
    OSCCONbits.SOSCEN=0;        //secondary osc disabled
    OSCCONbits.OSWEN=0;
}
void gpio_init()
{
    TRISGbits.TRISG0=0;
    LD1_IO=0;
    TRISGbits.TRISG1=0;
    LD3_IO=0;
    
    //push button
    RESET_READ_IO =1;
    TRISBbits.TRISB11=1;
    TRISBbits.TRISB15=1;
    TRISBbits.TRISB14=1;
    CNPUEbits.CNPUE14=1;
    //CNPUESET = 0x00008000;
    TERMOUT_IO=1;
    
    TRISFbits.TRISF2=1;     //U1RX
    TRISFbits.TRISF8=0;     //U1TX
    TRISFbits.TRISF4=1;     //U2RX
    TRISFbits.TRISF5=0;     //U1TX
    
    /*
    TRISFbits.TRISF4=1;     //U2RX
    TRISFbits.TRISF5=0;     //U2TX
    
    TRISDbits.TRISD14=1;    //U4RX
    TRISDbits.TRISD15=0;    //U4TX
    */
    TRISFbits.TRISF12=1;    //U5RX
    TRISFbits.TRISF13=0;    //U5TX
    
    //GPS MODULE RESET PIN
    RESET_IO=0;     //op
    //RESET=1;       //high
    TRISDbits.TRISD6 =0;
    LATDbits.LATD6=1;
    
    TRISAbits.TRISA14 =0;
    TRISAbits.TRISA15 =0;
    //LATAbits.LATA14=1;
   // RESET=0;
    
}
void uart1_init()   //modem
{
    U1MODEbits.ON=0;       //UART disabled
    U1MODEbits.UEN=0;
    U1MODEbits.WAKE=1;
    U1MODEbits.PDSEL=0;    //8 bit data, no parity
    U1MODEbits.STSEL=0;    //1 stop bit
    
    IEC0bits.U1RXIE=1;     //rx interrupt
    IFS0bits.U1RXIF=0;
    
    //IEC0bits.U1TXIE=1;      //tx interrupt
    //IFS0bits.U1TXIF=0;
    
    //IEC0bits.U1EIE=1;
    //IFS0bits.U1EIF=0;
    
    //U1STAbits.UTXISEL=0;
    U1STAbits.URXISEL=0;     //INTERRUPT ENABLED WEN BUFFER RECEIVES ANYTHING
    
    
    U1MODEbits.BRGH=0;
    U1BRG=0x138;           //baud rate 9600
    
    IPC6bits.U1IP=7;  //commented for proper timer working
    IPC6bits.U1IS=3;
    U1STAbits.OERR=0;
    
    INTCONSET=_INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
    //turn on interrupt
    U1STAbits.URXEN=1;
    U1STAbits.UTXEN=1;
    U1MODEbits.ON=1;       //UART enabled

}
void uart2_init()   //power source 
{
    U2MODEbits.ON=0;       //UART disabled
    U2MODEbits.UEN=0;
    U2MODEbits.WAKE=1;
    U2MODEbits.PDSEL=0;    //8 bit data, no parity
    U2MODEbits.STSEL=0;    //1 stop bit
    
    IEC1bits.U2RXIE=1;     //rx interrupt
    IFS1bits.U2RXIF=0;
    
    //IEC0bits.U1TXIE=1;      //tx interrupt
    //IFS0bits.U1TXIF=0;
    
    //IEC0bits.U1EIE=1;
    //IFS0bits.U1EIF=0;
    
    //U1STAbits.UTXISEL=0;
    U2STAbits.URXISEL=0;     //INTERRUPT ENABLED WEN BUFFER RECEIVES ANYTHING
    
    
    U2MODEbits.BRGH=0;
    U2BRG=0x138;           //baud rate 9600
    //U2BRG=0x19;           //baud rate 115200
    
    IPC8bits.U2IP=7;  //commented for proper timer working
    IPC8bits.U2IS=2;
    U2STAbits.OERR=0;
    
    INTCONSET=_INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
    //turn on interrupt
    U2STAbits.URXEN=1;
    U2STAbits.UTXEN=1;
    U2MODEbits.ON=1;       //UART enabled

}

void uart4_init()   //WIFI
{
    U4MODEbits.ON=0;       //UART disabled
    //U4MODEbits.//UEN=0;
    U4MODEbits.WAKE=1;
    U4MODEbits.PDSEL=0;    //8 bit data, no parity
    U4MODEbits.STSEL=0;    //1 stop bit
    
    IEC2bits.U4RXIE=1;     //rx interrupt
    IFS2bits.U4RXIF=0;
    
    //IEC0bits.U1TXIE=1;      //tx interrupt
    //IFS0bits.U1TXIF=0;
    
    //IEC0bits.U1EIE=1;
    //IFS0bits.U1EIF=0;
    
    //U1STAbits.UTXISEL=0;
    U4STAbits.URXISEL=0;     //INTERRUPT ENABLED WEN BUFFER RECEIVES ANYTHING
    
    
    U4MODEbits.BRGH=0;
    //U4BRG=0x19;           //baud rate 115200
    U4BRG=0x138;           //baud rate 9600
    
    IPC12bits.U4IP=7;  //commented for proper timer working
    IPC12bits.U4IS=2;
    U4STAbits.OERR=0;
    
    INTCONSET=_INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
    //turn on interrupt
    U4STAbits.URXEN=1;
    U4STAbits.UTXEN=1;
    U4MODEbits.ON=1;       //UART enabled

}

void uart5_init()   //gps module
{
    U5MODEbits.ON=0;        //UART disabled
    //U5MODEbits.UEN=0;
    U5MODEbits.WAKE=1;
    U5MODEbits.PDSEL=0;    //8 bit data, no parity
    U5MODEbits.STSEL=0;    //1 stop bit
    
    IEC2bits.U5RXIE=1;     //rx interrupt
    IFS2bits.U5RXIF=0;
    
    //IEC0bits.U1TXIE=1;      //tx interrupt
    //IFS0bits.U1TXIF=0;
    
    //IEC0bits.U1EIE=1;
    //IFS0bits.U1EIF=0;
    
    //U1STAbits.UTXISEL=0;
    U5STAbits.URXISEL=0;     //INTERRUPT ENABLED WEN BUFFER RECEIVES ANYTHING
    
    
    U5MODEbits.BRGH=0;
    U5BRG=0X138;//0x115200           //0X138baud rate 9600
    
    IPC12bits.U5IP=7;  //commented for proper timer working
    IPC12bits.U5IS=3;
    U5STAbits.OERR=0;
    
    INTCONSET=_INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
    //turn on interrupt
    U5STAbits.URXEN=1;
    U5STAbits.UTXEN=1;
    U5MODEbits.ON=1;       //UART enabled

}
void timer1_init()
{
    
    T1CONbits.TON=0;   //STOPS TIMER & RESETS CONTROL REGESTER
    T1CONbits.TCKPS=0;
    //T1CONbits.TCS=0;
    
    TMR1=0x0;          //CLEAR TIMER REGISTER
    PR1=0xBA03;        //PERIOD MATCH INTERRUPT ON 1MSEC
   
    IPC1bits.T1IP=7;   //7
    IFS0bits.T1IF=0;
    IEC0bits.T1IE=1;
    
    INTCONSET=_INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
    T1CONbits.TON=1;
    //IFS0CLR=0X0010;  //FLAG RESET
    //IEC0SET=0X0010;  //TIMER 1 INTERRUPT ENABLED
    //T1CONCLR=0x0032; //tcs 0
    //INTCONbits.MVEC=0; //single vector mode
    
    //INTSTAT=0x0004;
    //IPC1SET=0X0005;  //PRIORITY
    //IPC1SET=0X0001;  //SUBPRIORITY
    //T1CONSET=0X8000; //START TIMER
    //__builtin_enable_interrupts();

}
void timer2_init()
{
    T2CONbits.TON=0;
    T2CONbits.TCKPS=0;
    T2CONbits.TCS=0;   //ADDED
    //T2CONbits.T32=1;
    PR2=0x5D01;   //0d23809
    TMR2=0;
    IPC2bits.T2IP=7;      //7
    IFS0bits.T2IF=0;
    IEC0bits.T2IE=1;
    INTCONSET=_INTCON_MVEC_MASK;
    __builtin_enable_interrupts();
    T2CONbits.TON=1;

}

void ADC_init()
{
    //AD1CON1CLR = _AD1CON1_ON_MASK;
    AD1PCFG             = 0XFFFF;  // all port B pin as digital input pin
    AD1PCFGbits.PCFG2   = 0;       //set pin AN2 as Analog input
    AD1PCFGbits.PCFG3   = 0;       //set pin AN3 as Analog input
  //AD1PCFGbits.PCFG4   = 0;
  //AD1PCFGbits.PCFG5   = 0;
  //AD1PCFGbits.PCFG6   = 0;
  //AD1PCFGbits.PCFG7   = 0;
    
    //input scan
    AD1CSSL             = 0x0000; // skip all analog channels for input scanning
    AD1CSSLbits.CSSL2   = 1;      //select AN2  for input scanning //BUF0
    AD1CSSLbits.CSSL3   = 1;      //select AN3  for input scanning //BUF1
    
    AD1CON1bits.FORM    = 0;      ///DATA OUTPUT FORMAT IS UNSIGNED INTEGER
    AD1CON1bits.SSRC    = 7;      //INTERNAL COUNTER ENDS SAMPLEING AND START CONVERSION(AUTO CONVERT).
    AD1CON1bits.CLRASAM = 0;      // Normal operation, buffer contents will be overwritten by the next conversion sequence
    AD1CON2bits.VCFG    = 0;      // Internal voltage reference AVdd, AVss
    AD1CON2bits.CSCNA   = 1;      //SCAN INPUTS
    AD1CON2bits.SMPI    = 7;      //Interrupts at the completion of conversion for each 8th sample/convert sequence
    AD1CON2bits.BUFM    = 0;      // BUFFER CONFIGURED AS ONE 16- WORD BUFFER
    AD1CON2bits.ALTS    = 0;      //ALWAYS USE MUX A SETTINGS
    AD1CHS              = 0x00020000; // Connect RB2/AN2 as CH0 input
    AD1CON3bits.SAMC    = 1;       // Sample time
    AD1CON3bits.ADRC    = 0;       // AD conversion clock source from system clock 
    AD1CON3bits.ADCS    = 19;      //ADC Conversion Clock Select bits
    AD1CON1bits.SIDL    = 0;       //CONTINUE IN IDEAL MODE
    AD1CHSbits.CH0NA    = 0;       // Channel multiplexer A negative is Vrefl   
    IPC6bits.AD1IP      = 2;       //INTERRUPT priority  
   // IPC6bits.AD1IS =1;
    //IPCxPriority(INT_VECTOR_AD1, 2, 2);
     
    IFS1bits.AD1IF      = 0; //
    IEC1bits.AD1IE      = 1;
    //AD1CON1SET        = _AD1CON1_ON_MASK;
    AD1CON1bits.ADON    = 1;       // turn ON the ADC
    AD1CON1bits.ASAM    = 1;       //ADC Sample Auto-Start bit

}