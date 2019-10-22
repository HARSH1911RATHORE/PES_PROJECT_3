#ifndef _MEMORY_TEST_H_
#define _MEMORY_TEST_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
void write_pattern(uint32_t * loc, size_t length, int8_t seed);
uint32_t *verify_pattern(uint32_t * loc, size_t length, int8_t seed);
uint32_t *  get_address(uint32_t * loc, int offset);
void gen_pattern(unsigned int length,unsigned int seed);
void invert(uint32_t * loc, size_t offset);
void invert_block(uint32_t * loc, size_t length);
void write_memory(uint32_t * loc,uint8_t offset, uint32_t value);
uint32_t * display_memory(uint32_t *Block_Pointer,uint8_t Data_words_to_read );
void free_words(uint32_t *Block_Pointer,unsigned int length);
uint32_t * allocate_words(unsigned int length);
int error_code(int err);
//void log_data(uint32_t * Block_Pointer,uint8_t length);
#endif
