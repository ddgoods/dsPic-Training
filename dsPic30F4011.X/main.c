#include "Config.h"
#include "main.h"

uint16_t Hb=0; //Hb LED time

int main(void)
{
    Timer_1_Init(); //Initiaize Timer 1 periodic interrupt
    _TRISD0 = 0; //Initilize RD0 as an output
    
    while(1)
    {
       if(Hb > 100 && _RD0 == 0) //if 100ms pass & Hb LED off
       {
           _LATD0 = 1; //turn on LED
           Hb = 0;     //reset Hb variable
       }
       if(Hb > 100 && _RD0 == 1) //if 100ms pass & Hb LED on
       {
           _LATD0 = 0; //turn off LED
           Hb = 0;   //reset Hb variable
       }

    }
}

void Timer_1_Init(void)
{
    T1CONbits.TGATE = 0; //disable gate time accumulation
    T1CONbits.TCKPS = 2; //1:64 prescalar
    T1CONbits.TSYNC = 0; //do not sync to external clock
    T1CONbits.TCS = 0; //using internal clock
    
    PR1 = ONE_MILLIS;
    
    IEC0bits.T1IE = 1; //enable timer 1 interrupt
    IPC0bits.T1IP = 6; // priority 6
    IFS0bits.T1IF = 0; //clear interrupt flag 
    T1CONbits.TON =1;  //start timer
}

void __attribute__((interrupt, auto_psv)) _T1Interrupt( void )               
{
    Hb++;               //increment Hb variable
    IFS0bits.T1IF = 0; //clear interrupt flag
}