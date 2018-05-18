#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "rc6.h"


#define TOTAL_COL 4
#define TOTAL_ROW 4

int button_press(uint8_t pin);
void drive_row(uint8_t pin,uint8_t val);

//remote key codes
//add keycodes 
uint32_t key_codes[TOTAL_ROW][TOTAL_COL] = {
                                            {0x0,0x0,0x0,0x0},
                                            {0x0,0x0,0x0,0x0},
                                            {0x0,0x0,0x0,0x0},
                                            {0x0,0x0,0x0,0x0}

                                           };

//col pins for sensing the button press.
uint8_t col_pins[] = {2 , 5, 7, 6 };        //PB2 , PB5 , PB7 , PB6


//row pins for driving the rows one by one.
uint8_t row_pins[] = {3 , 4, 6, 7};         //PD3 , PD4 , PD6 , PD7



int main() 
{

    DDRD = ((1 << PD3) | (1 << PD4) | (1 << PD6) | (1 << PD7));             //setting row pins as output.
    PORTD |= ((1 << PD3) | (1 << PD4) | (1 << PD6) | (1 << PD7));           //initially all rows driven HIGH.
    while(1)
    {
        for(uint8_t row = 0;row < TOTAL_ROW; row++) 
        {

          drive_row(row,0);
          for(uint8_t col = 0;col < TOTAL_COL; col++) 
          {
                
               if(button_press(col))
                {
                    
                    start_tx_rc6(key_codes[row][col]);
                }
          }
          drive_row(row,1);                   
        }
              
    }

     return 0;
}




void drive_row(uint8_t pin,uint8_t val)
{
  
  if(!val)
      PORTD &= ~(1 << (row_pins[pin]));
  else
       PORTD |= (1 << (row_pins[pin]));

}



int button_press(uint8_t pin) 
{

    uint8_t p = col_pins[pin];
    uint8_t button_state,button_state2;
    while(1)
    {
         button_state = !((PINB & (1 << p)) >> p);
         _delay_ms(5);                              //debouncing..and also determines the row scan rate.
         button_state2 = !((PINB & (1 << p)) >> p);

         if(button_state == button_state2)
             break;
    }
    

    return (button_state);
  
}

