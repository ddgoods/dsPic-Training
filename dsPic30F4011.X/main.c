#include "Config.h"
#include "main.h"


int main(void)
{
    _TRISD0 = 0; //Initilize RD0 as an output
    
    while(1)
    {
        _LATD0 = 1; //set RD0 high
        __delay_ms(100);
        _LATD0 = 0; //set RD0 low
        __delay_ms(100);
    }
}
