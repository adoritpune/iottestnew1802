#define LD1_OUT       PORTGbits.RG0
#define LD1_IO        TRISGbits.TRISG0
#define LD1_IOLAT     LATGbits.LATG0

/*LD2*/
#define LD2_OUT       PORTGbits.RG1
#define LD2_IO        TRISGbits.TRISG1
#define LD2_IOLAT     LATGbits.LATG1

/*LD4*/
#define LD4_OUT       PORTFbits.RF1
#define LD4_IO        TRISFbits.TRISF1
#define LD4_IOLAT     LATFbits.LATF1

/*ld3*/
#define LD3_OUT       PORTAbits.RA6
#define LD3_IO        TRISAbits.TRISA6
#define LD3_IOLAT     LATAbits.LATA6

/*reset read rb11*/
#define RESET_READ_IO    TRISBbits.TRISB11
#define RESET_READ       PORTBbits.RB11

/*reset*/
#define RESET_IO TRISDbits.TRISD6     //op
#define RESET    LATDbits.LATD6      //high

/*I2C PINS*/
#define SDA1IO TRISAbits.TRISA15     //DATA OUTPUT
#define SDA    LATAbits.LATA15     //DATA OUTPUT
#define SDA_RD  PORTAbits.RA15

#define SCL1IO TRISAbits.TRISA14     //CLOCK OUTPUT
#define SCL    LATAbits.LATA14     //DATA OUTPUT

#define TERMOUT_IO  TRISBbits.TRISB15     //DATA OUTPUT
#define TERMOUT     LATBbits.LATB15     //DATA OUTPUT
#define TERMOUT_RB  PORTBbits.RB15

//POWER SOURCE DATA
#define START_ADDRESS 0xA000A710         //10000TH LOCATION  //2710
#define PS_WIRESPEED      0x00
#define PS_SETCURRENT     0x01
#define PS_SETVOLTAGE     0x02
#define PS_ACTUALCURRENT  0x03
#define PS_ACTUALVOLTAGE  0x04
/*#define PS_MATERIAL       0x05
#define PS_PROCESS        0x06
#define PS_WELDMODE       0x07
#define PS_CRATERCURRENT  0x08
#define PS_CRATERVOLTAGE  0x09
#define PS_DIAMETER       0x0A
#define PS_GAS            0x0B
#define PS_HF_STATUS      0x0C
#define PS_CARRIAGE_SPEED 0x0D
#define PS_CARRIAGE_STATUS 0x0E
#define PS_WELDSTATUS     0x0F
#define PS_ARCONTIME      0x10
#define PS_ERROR          0x11*/



unsigned int __attribute__((address (START_ADDRESS + PS_WIRESPEED*2)))          iwirespeed;
unsigned int __attribute__((address (START_ADDRESS + PS_SETCURRENT*2))) 	    isetcurrent;
unsigned int __attribute__((address (START_ADDRESS + PS_SETVOLTAGE*2))) 	    isetvoltage;
unsigned int __attribute__((address (START_ADDRESS + PS_ACTUALCURRENT*2)))      iactualcurrent;
unsigned int __attribute__((address (START_ADDRESS + PS_ACTUALVOLTAGE*2)))      iactualvoltage;
//unsigned int __attribute__((address (START_ADDRESS + PS_MATERIAL*2)))           imaterial;
#define DECODE_DELAY 1000

//changed by PPC
#define USER_ID_ADDR		 0x0022  //16 location for Machine ID
#define INDEX_ID_ADDR        0x0002  //20 location for Machine Name
#define MACHINE_I_ADDR       0x0036  //16 location for Machine max Current & slope
#define LATITUDE_ADDR        0x0047
#define LONGITUDE_ADDR       0x0058
#define PROVISION            0X0069

/*

#define MACHINE_ID_ADDR		 0x0011
#define MODEL_NAME_ADDR		 0x0020
#define LATITUDE_ADDR        0x002F
#define LONGITUDE_ADDR       0x003E
#define PROVISION            0X004D
*/

/*#define MACHINE_ID_ADDR		 0x004D
#define MODEL_NAME_ADDR		 0x004D
#define LATITUDE_ADDR        0x004D
#define LONGITUDE_ADDR       0x004D
#define PROVISION            0X004D*/

#define VALIDLOCATIONDLY    250
#define INVALIDLOCATIONDLY  5000
//---------for 10/12/15 sec data ---------//

#define IOTDATASEC          15//10 //15         //12
#define ACTUALDATACNT       74//49 //74(0-74=75)  //59(0-59 = 60)
#define TORCHSTATUSCNT      134//89 //134(0-134=135) //107(0-107 = 108)
#define HTTPDATABYTES       960 //15sec - 1055 10sec- 960 12sec- 998											