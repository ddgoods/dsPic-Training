#include "Config.h"
#include "main.h"

 uint16_t counter = 0; //global counter varible used to update duty cycle register to create PWM effect
 
int main(void)
{
    uint8_t x =0; // variable to switch between increment and decrement states
    PWM_Init(); //init function for PWM of LED
    
    while(1)
    {
        __delay_us(100);
        /*counter will increase as long as counter variable is less than 2048,
         else it will switch to x = 1 state to decrease counter variable */
        if(x == 0) //increment  when x = 0
        {
            counter++;        
            if(counter > 9998)
            {
                x = 1;
            }
        }
        /*counter will decrease as long as counter variable is greater than 1,
         else it will switch to x = 0 state to increase counter variable */
        if(x == 1) //decrement  when x = 1
        {
            counter--;
            if( counter < 1)
            {
                x = 0;
            }
        }
        PDC1 = counter; // update duty cycle register
        
       
    }
}

void PWM_Init( void )
{
    _TRISE0 = 0; // make sure PWM pins 38 are set to be outputs
    _RE0 = 0; // clear the output
 
    PTCONbits.PTOPS = 0; // PWM timer post-scale 1:1
    PTCONbits.PTCKPS = 0; // PWM timer pre-scale 1:1
    PTCONbits.PTMOD = 2; // PWM operates in Up-down Mode continuously
 
    PTMR = 0; // PWM counter value, start at 0
 
    PTPER = 4999; // PWM Timebase period 1ms
    PWMCON1bits.PMOD1 = 1; // PWM in independant mode
    PWMCON1bits.PEN1L = 1; // PWM Low pin enabled (direction control later?)
  
 
    // Duty Cycle has a max value of 2xPeriod since output  
    // can change on rising or falling edge of Tcy
    PDC1 = counter; // PWM#1 Duty Cycle register 
 
    PTCONbits.PTEN = 1; // Enable PWM Timerbase!
}