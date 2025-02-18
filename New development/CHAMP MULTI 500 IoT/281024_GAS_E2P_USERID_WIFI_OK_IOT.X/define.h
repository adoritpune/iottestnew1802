/* 
 * File:   define.h
 * Author: admin
 *
 * Created on 12 July, 2021, 9:35 AM
 */

#ifndef DEFINE_H
#define	DEFINE_H

#ifdef	DEFINE_H
//DEVCFG0 device configuration word 0
#pragma config CP        = OFF    //code protect bit-protection disabled-program memory read/modification by external programming device 
#pragma config BWP       = OFF   //boot flash write protect bit- protection disabled- boot flash memory modification during execution
#pragma config PWP       = OFF   //program flash write protect bit- protection disabled-
#pragma config ICESEL    = ICS_PGx1// PGEC1 and PGED1 selected
#pragma config DEBUG     = OFF //background debugger enable bit- debugger disabled

//DEVCFG1
#pragma config FWDTEN    = OFF    //wdt Enable bit-wdt disabled -canbe enabled in software
#pragma config WDTPS     = PS1     //wdt postscaler bit-wdt postscaler 1:1
#pragma config FCKSM     = CSDCMD  //clk switching/monitor selection configuration-disabled clk switch fscm
#pragma config FPBDIV    = DIV_1  //Pb_clk is Sys_clk/1
#pragma config OSCIOFNC  = OFF  //CLKO enable bit- clk out disabled
#pragma config POSCMOD   = HS    //CHECK*****************************************
#pragma config IESO      = OFF      //internal external switchover bit-disabled
#pragma config FSOSCEN   = OFF   //secondary oscillator enable bit-disabled
#pragma config FNOSC     = FRCPLL  //CHECK*********************************************

//DEVCFG2
#pragma config FPLLODIV  = DIV_2   //PLL output divided by 1
#pragma config UPLLEN    = OFF       //usb pll enable bit-disabled
#pragma config UPLLIDIV  = DIV_1   //usb pll divided by 1
#pragma config FPLLMUL   = MUL_24   //pll multiplier bits
#pragma config FPLLIDIV  = DIV_1   //pll input divider bits
//input divider is 2 by default. mltiplier 24 and output divider 2-> 8mhz/2=4   4*24=96mhz    96/2=48MHZ

//DEVCFG3
#pragma config FVBUSONIO = OFF     //usb Vbuson selection bit-disabled
#pragma config FUSBIDIO  = OFF
#pragma config FCANIO    = OFF




#endif

#endif	/* DEFINE_H */

