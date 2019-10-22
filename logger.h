#ifndef _LOGGER_H_
#define _LOGGER_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
void log_data(uint32_t * Block_Pointer,uint8_t length);
int log_status(int status);
int logger_error_code(int log_err);
void log_get_address(uint32_t * loc, int offset);
void log_invert(uint32_t * loc, int offset, uint32_t inverted);
void log_invert_block(uint32_t * loc,uint8_t i,uint32_t inverted);
//void log_write_pattern(uint32_t * loc, size_t length, int8_t seed,uint32_t pat);
void log_verify_pattern(uint32_t * loc,uint8_t i);
void log_free_memory();
void log_string(uint8_t string);
#endif
