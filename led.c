#include "led.h"
void led_test()
{
	if (err == 0)
    {

        LED_BLUE_ON();
        LED_RED_OFF();
        LED_GREEN_OFF();


    }
    else if (err == 1)
    {
        LED_BLUE_OFF();
        LED_RED_ON();
        LED_GREEN_OFF();
    }
    else if (err == 2)
    {
        LED_BLUE_OFF();
        LED_RED_OF();
        LED_GREEN_OFF();
    }
    else if (err==3)
    {
        LED_BLUE_OFF();
        LED_RED_OF();
        LED_GREEN_OFF();
    }
    else
    {
    	logger_error_code(err);
        return	(printf("\n\rOperation Unsuccessful - Unknown fault \n\r"));
    }
}
