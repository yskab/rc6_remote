#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "rc6.h"


static void delay_us(uint8_t);
static void tx(uint8_t, uint8_t, uint8_t);


void start_tx_rc6(uint32_t button_val)
{


  
    uint32_t mask = 0x80000000;
    int8_t shift = 31;
    DDRC = (1 << PC4);                                                //ir output pin.
    for(uint8_t i = 0;i < 7; i++)
    {                                                         

        switch(i)
        {

            case 0:    tx(RC6_LEADER_COUNT,RC6_LEADER_BLANK,1);       //leader pulse
                       break;
            case 1: 
            case 2:
            case 3:    tx(RC6_BIT_ONE_COUNT,RC6_BIT_ONE_BLANK,1);     //one pulse
                       break;

            case 4:    tx(RC6_BIT_ZERO_COUNT,RC6_BIT_ZERO_BLANK,0);   //zero pulse
                       break;

            case 5:    tx(RC6_TRAILER_COUNT,RC6_TRAILER_BLANK,0);     //trailer pulse
                       break;

            case 6:    while(shift >= 0)                              //data pulse
                       {
                         if((button_val & mask) >> shift)
                             tx(RC6_BIT_ONE_COUNT,RC6_BIT_ONE_BLANK,1);
                         else
                             tx(RC6_BIT_ZERO_COUNT,RC6_BIT_ZERO_BLANK,0);

                         mask = mask >> 1;
                         shift--;
                      }
                      break;
                    
        }
    }
    _delay_ms(RC6_DELAY);  // delay for receiver
}




static void tx(uint8_t toggle_count, uint8_t blank_width, uint8_t trail)
{                                                                               

   
    if(!trail)           
    {
        PORTC &= ~(1 << (PC4));
        delay_us(blank_width);

    }   

    for(uint16_t i = 0;i<toggle_count;i++)
    {
        PORTC |= (1 << (PC4));
        _delay_us(13);
        PORTC &= ~(1 << (PC4));    
        _delay_us(13);
    }

    if(trail)
    {
        PORTC &= ~(1 << (PC4));
        delay_us(blank_width);

    
    }

}


static void delay_us(uint8_t delay_count)
{

  for(int i = 0;i < delay_count;i++)
    _delay_us(50);
  
}




