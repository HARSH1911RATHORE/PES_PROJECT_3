
#include "led.h"

uint32_t constant_value=400000;      //TAKE A CONSTANT VALUE OF 400000 AND DELAY IT FOR THE
										//THE REQUIRED TIME
uint32_t j=0;
void Delay(uint32_t time)
{									//WASTE THE CLOCK CYCLE FOR PARTICULAR VALUE TO GET THE
										//DELAY OF THE LED
uint32_t clock_ticks=(constant_value* time)/(500);
for (j=0;j<clock_ticks;j++);
}
void led_blue()
{
        LED_BLUE_ON();    // TURN THE BLUE LED ON FOR INITIAL PERIOD
        Delay(200);
        LED_BLUE_OFF();  // TURN IT OFF AFTER THE DELAY
        Delay(100);
}
void led_red()
{

        LED_RED_ON();     // TURN THE BLUE LED ON FOR ERRORS DURING MEMORY TESTS
        Delay(200);
        LED_RED_OFF();   // TURN IT OFF AFTER THE DELAY
        Delay(100);
}
void led_green()
{
        LED_GREEN_ON();   // TURN THE GREEN LED ON AFTER SUCCESFULLY COMPLETING THE OPERTION
}

