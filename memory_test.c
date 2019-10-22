
#include "memory_test.h"
#include "logger.h"

extern int err;


unsigned int block2[1000];
unsigned int pat[100];
int error_code(int err)
{


    if (err == 0)
    {
    	logger_error_code(err);
        return	(printf("\n\r Operation Started \n\r"));
    }
    else if (err == 1)
    {
    	logger_error_code(err);
        return (printf("\n\r Warning: Buffer has not been allocated yet \n\r"));
    }
    else if (err == 2)
    {
    	logger_error_code(err);
        return	(printf("\n\r Memory Out of Bounds attempted - Exited with error code 2 \n\r"));
    }
    else if (err==3)
    {
    	logger_error_code(err);
        return (printf("\n\rERROR ON VERIFYING \n\r"));
    }
    else
    {
    	logger_error_code(err);
        return	(printf("\n\rOperation Successful \n\r"));
    }


}
uint32_t * allocate_words(int length)
{

    uint32_t *Block_Pointer;
    int i;
    Block_Pointer = (uint32_t *)malloc(length*4);
    if (Block_Pointer!=NULL)
    {
        err=0;
        error_code(err);
    }
    else
    {
        err=2;
        error_code(err);
    }


    for(i= 0; i<length; i++)            /*Initialize all memory blocks to 0*/
    {
        *(Block_Pointer+i)=0;
    }

    return Block_Pointer;
}

//Free Word function
void free_words(uint32_t *Block_Pointer,int length)
{
    int i;
    log_string(1);
    printf("\n\rFREE THE MEMORY\n\r");
    for (i=0; i<length; i++)
    {
        if (Block_Pointer!=NULL)
        {
            free(Block_Pointer);
            Block_Pointer = NULL;
        }

        else
        {
            err=1;
            error_code(err);
            free(Block_Pointer);
            Block_Pointer = NULL;
        }
    }


}


//Read from memory
uint32_t * display_memory(uint32_t *Block_Pointer,uint8_t Data_words_to_read )
{
    int i;
    printf("\n\r DISPLAY MEMORY PATTERN\n\r");
    log_string(2);
    for(i=0; i<Data_words_to_read; i++)
    {

        printf("  Data at %p address is %08d \n\r",(Block_Pointer) +i,Block_Pointer[i]);
    }

    log_data(Block_Pointer, Data_words_to_read);
    return (Block_Pointer);
}

void write_memory(uint32_t * loc,uint8_t offset, uint32_t value)
{
    log_string(4);
    printf("\n\rWRITE DATA TO MEMORY\n\r");
    loc[0+offset] = value;
}

//Invert Function


void invert_block(uint32_t * loc, size_t length)
{
    int i,data,inverted;
    for(i=0; i<length; i++)
    {
        data=*(loc+i);
        inverted = 0xFFFFFFFF^data;
        									// Exor with 1 togges the bit
        *(loc+i) = inverted;
        printf(" inverted data at %p address is %08x \n\r",(loc+i),inverted);

        log_invert_block(loc,i,inverted);
    }

}
void invert(uint32_t * loc, size_t offset)
{
    int data,inverted;
    log_string(3);

    data=loc[offset];
    inverted = 0xFFFFFFFF^data;

    loc[offset] = inverted;

    printf(" \n\rInverted data at %p address is %08x \n\r",(loc+offset),inverted);
    printf("\n\r");
    log_invert(loc,offset,inverted);
}

uint32_t *  get_address(uint32_t * loc, int offset)
{
    log_get_address(loc,offset);
    printf("  Address at offset %d is %p \n\r",offset,loc+offset);
    return (loc+offset);

}

void write_pattern(uint32_t * loc, size_t length, int8_t seed)
{
    int i;
    gen_pattern(length, seed);
    printf("\n\r WRITE PATTERN TO MEMORY\n\r");
    log_string(1);
    //log_write_pattern(  loc, length,  seed);
    for (i=0; i<length; i++)
    {
        loc[i]=pat[i];
        printf("%p\n\r",loc[i]);
    }

}


uint32_t * verify_pattern(uint32_t * loc, size_t length, int8_t seed)
{
    int i;

    gen_pattern(length, seed);
    //log_verify_pattern(loc,length,seed);
    log_string(5);
    for (i=0; i<length; i++)
    {
        block2[i]=pat[i];
        printf("%d\n\r",block2[i]);
    }
    for (i=0; i<length; i++)
    {
        if(block2[i]==loc[i])
        {
            //err=4;
            //error_code(err);
            //printf("\n\rNO ERROR ON VERIFYING\n\r");
            LED_BLUE_OFF();
            LED_RED_OFF();
        }
        else
        {
            err=3;
            error_code(err);
            printf("\n\rAddress %p contains value %p\n\r",&loc[i],loc[i]);
            log_verify_pattern(loc,i);
            LED_BLUE_OFF();
            LED_RED_ON();
        }
    }





    return (loc);

}



