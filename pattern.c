

//#include"pattern.h"
//typedef struct tagMTRand                                        //defining a structure data type of MTRand
//{
//    unsigned int mt[STATE_VECTOR_LENGTH];
//    int index;                                                    //using the index to specify the array elements the value points to
//} Random;
//
//void gen_pattern(unsigned int length,unsigned int seed)
//{
//    unsigned int i;
//
//    Random r = seedRand(seed);
//    for(i=0; i<length; i++)
//    {
//        pat[i]=genRand(&r);
//        //PRINTF("%d\n\r", pat[i]);
//    }
//
//}
//
//
//void m_seedRand(Random* rand, unsigned int seed)
//{
//    rand->mt[0] = seed & 0xff;
//    for(rand->index=1; rand->index<STATE_VECTOR_LENGTH; rand->index++)
//    {
//        rand->mt[rand->index] = (6069 * rand->mt[rand->index-1]) & 0xff;
//    }
//}
//
///**
//* Creates a new random number generator from a given seed.
//*/
//Random seedRand(unsigned int seed)
//{
//
//    Random rand;
//    m_seedRand(&rand, seed);
//    return rand;
//}
//
//
///**
// * Generates a pseudo-randomly generated long.
// */
//unsigned int genRandLong(Random* rand)
//{
//
//    unsigned int y;
//    static unsigned int mag[2] = {0x0, 0x99}; /* mag[x] = x * 0x9908b0df for x = 0,1 */
//    if(rand->index >= STATE_VECTOR_LENGTH || rand->index < 0)
//    {
//        /* generate STATE_VECTOR_LENGTH words at a time */
//        int kk;
//        if(rand->index >= STATE_VECTOR_LENGTH+1 || rand->index < 0)
//        {
//            m_seedRand(rand, 43);
//        }
//        for(kk=0; kk<STATE_VECTOR_LENGTH-STATE_VECTOR_M; kk++)
//        {
//            y = (rand->mt[kk] & UPPER_MASK) | (rand->mt[kk+1] & LOWER_MASK);
//            rand->mt[kk] = rand->mt[kk+STATE_VECTOR_M] ^ (y >> 1) ^ mag[y & 0x1];
//        }
//        for(; kk<STATE_VECTOR_LENGTH-1; kk++)
//        {
//            y = (rand->mt[kk] & UPPER_MASK) | (rand->mt[kk+1] & LOWER_MASK);
//            rand->mt[kk] = rand->mt[kk+(STATE_VECTOR_M-STATE_VECTOR_LENGTH)] ^ (y >> 1) ^ mag[y & 0x1];
//        }
//        y = (rand->mt[STATE_VECTOR_LENGTH-1] & UPPER_MASK) | (rand->mt[0] & LOWER_MASK);
//        rand->mt[STATE_VECTOR_LENGTH-1] = rand->mt[STATE_VECTOR_M-1] ^ (y >> 1) ^ mag[y & 0x1];
//        rand->index = 0;
//    }
//    y = rand->mt[rand->index++];
//    y ^= (y >> 11);
//    y ^= (y << 7) & TEMPERING_MASK_B;
//    y ^= (y << 15) & TEMPERING_MASK_C;
//    y ^= (y >> 18);
//    return y;
//}
//
///**
// * Generates a pseudo-randomly generated double in the range [0..1].
// */
//unsigned int genRand(Random* rand)
//{
//    return(genRandLong(rand) / 0xfffff);
//}
//
//
