//#ifndef _LED_H_
//#define _LED_H_
//#include <stdlib.h>
//#include <stdio.h>
//#include <stdint.h>
//#include "board.h"
//#include "peripherals.h"
//#include "pin_mux.h"
//#include "clock_config.h"
//#include "MKL25Z4.h"
//#include "fsl_debug_console.h"
//void led_test();
//void Delay(uint32_t time);
//#endif
#ifndef _LED_H_
#define _LED_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
//void led_test();
void led_red();
void led_green();
void led_blue();
void Delay(uint32_t time);
#endif
