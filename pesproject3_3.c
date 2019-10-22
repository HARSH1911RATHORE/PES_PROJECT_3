//unit test install and implement,
//change all int to unit,
//malloc,
//write different function files ,
//make all function return types to set global variable error code
//Get all the checks and



#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "logger.h"
#include "memory_test.h"
#include "led.h"


/*
 * @brief   Application entry point.
 */

//Error Code Function Logger
#define UPPER_MASK		0x8000
#define LOWER_MASK		0x7fff
#define TEMPERING_MASK_B	0x9d2c
#define TEMPERING_MASK_C	0xefc60000
#define STATE_VECTOR_LENGTH 62
#define STATE_VECTOR_M      39 /* changes to STATE_VECTOR_LENGTH also require changes to this */

typedef struct tagMTRand                                        //defining a structure data type of MTRand
{
    unsigned int mt[STATE_VECTOR_LENGTH];
    int index;                                                    //using the index to specify the array elements the value points to
} Random;

unsigned int length=4;

extern unsigned int pat[100];
Random seedRand(unsigned int seed);
unsigned int genRandLong(Random* rand);
unsigned int genRand(Random* rand);
void m_seedRand(Random* rand, unsigned int seed);


void gen_pattern(unsigned int length,unsigned int seed);


int main(void)
{

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();

    PRINTF("Hello World\n\r");

    volatile static int i = 0 ;

    LED_RED_INIT(1);
    LED_GREEN_INIT(1);
    LED_BLUE_INIT(1);

    // int err = 0;
    //Errorcode default set to 0 sucess



    //Test Suite

    LED_BLUE_ON();
    uint32_t *test_space = allocate_words(length);
    PRINTF("\n\rAll the Available Adresses now are \n\r");
    for (i=0; i< length ; i++)
    {
        PRINTF("\n\r%d  Address of memory - %p     \n\r\r",i+1,test_space + i);


    }

	write_pattern( test_space,  length,  10);

    display_memory(test_space,length);
    PRINTF("\n\r");

    verify_pattern( test_space, length, 10);
    PRINTF("\n\r");
    led_test();


    write_memory(test_space,2,0xFFEE);
    PRINTF("\n\r");
    display_memory(test_space,length);
    PRINTF("\n\r");
    verify_pattern( test_space, length, 10);
    led_test();
    PRINTF("\n\r");

    PRINTF("\n\r");
    write_pattern( test_space,  length,  10);
    PRINTF("\n\r");
    display_memory(test_space,length);
    PRINTF("\n\r");
    verify_pattern( test_space, length, 10);
    PRINTF("\n\r");
    led_test();


    PRINTF("\n\r");
    invert(test_space,1);
    PRINTF("\n\r");
    display_memory(test_space,length);
    PRINTF("\n\r");
    verify_pattern(test_space, length, 10);
    led_test();
    PRINTF("\n\r");

    PRINTF("\n\r");
    invert(test_space,1);
    PRINTF("\n\r");
    display_memory(test_space,length);
    PRINTF("\n\r");
    verify_pattern( test_space, length, 10);
    led_test();
    PRINTF("\n\r");

    PRINTF("\n\r");
    get_address(test_space,3);
    PRINTF("\n\r");
    free_words(test_space,length);
    LED_BLUE_OFF();
    LED_GREEN_ON();
    LED_RED_OFF();

    PRINTF("\n\r");
    printf("\n\r");


    return 0 ;
}






void gen_pattern(unsigned int length,unsigned int seed)
{
    unsigned int i;

    Random r = seedRand(seed);
    for(i=0; i<length; i++)
    {
        pat[i]=genRand(&r);
        //PRINTF("%d\n\r", pat[i]);
    }

}


void m_seedRand(Random* rand, unsigned int seed)
{
    rand->mt[0] = seed & 0xff;
    for(rand->index=1; rand->index<STATE_VECTOR_LENGTH; rand->index++)
    {
        rand->mt[rand->index] = (6069 * rand->mt[rand->index-1]) & 0xff;
    }
}

/**
* Creates a new random number generator from a given seed.
*/
Random seedRand(unsigned int seed)
{

    Random rand;
    m_seedRand(&rand, seed);
    return rand;
}


/**
 * Generates a pseudo-randomly generated long.
 */
unsigned int genRandLong(Random* rand)
{

    unsigned int y;
    static unsigned int mag[2] = {0x0, 0x99}; /* mag[x] = x * 0x9908b0df for x = 0,1 */
    if(rand->index >= STATE_VECTOR_LENGTH || rand->index < 0)
    {
        /* generate STATE_VECTOR_LENGTH words at a time */
        int kk;
        if(rand->index >= STATE_VECTOR_LENGTH+1 || rand->index < 0)
        {
            m_seedRand(rand, 43);
        }
        for(kk=0; kk<STATE_VECTOR_LENGTH-STATE_VECTOR_M; kk++)
        {
            y = (rand->mt[kk] & UPPER_MASK) | (rand->mt[kk+1] & LOWER_MASK);
            rand->mt[kk] = rand->mt[kk+STATE_VECTOR_M] ^ (y >> 1) ^ mag[y & 0x1];
        }
        for(; kk<STATE_VECTOR_LENGTH-1; kk++)
        {
            y = (rand->mt[kk] & UPPER_MASK) | (rand->mt[kk+1] & LOWER_MASK);
            rand->mt[kk] = rand->mt[kk+(STATE_VECTOR_M-STATE_VECTOR_LENGTH)] ^ (y >> 1) ^ mag[y & 0x1];
        }
        y = (rand->mt[STATE_VECTOR_LENGTH-1] & UPPER_MASK) | (rand->mt[0] & LOWER_MASK);
        rand->mt[STATE_VECTOR_LENGTH-1] = rand->mt[STATE_VECTOR_M-1] ^ (y >> 1) ^ mag[y & 0x1];
        rand->index = 0;
    }
    y = rand->mt[rand->index++];
    y ^= (y >> 11);
    y ^= (y << 7) & TEMPERING_MASK_B;
    y ^= (y << 15) & TEMPERING_MASK_C;
    y ^= (y >> 18);
    return y;
}

/**
 * Generates a pseudo-randomly generated double in the range [0..1].
 */
unsigned int genRand(Random* rand)
{
    return(genRandLong(rand) / 0xfffff);
}


