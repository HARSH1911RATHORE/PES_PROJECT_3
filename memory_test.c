
#include "memory_test.h"
#include "logger.h"
#include"led.h"          //CALL THE HEADER FILES CONTAINING THE FUNCTIONS AND LIBRARY FUNCTIONS

static unsigned int err; //DECLARE err AS STATIC SO THAT VALUE IS RETAINED WITH
							//EVERY FUNCTION CALL
unsigned int block2[1000];   //DECLARE THE BLOCK2 SIZE WHICH CONTAINS THE CONTENTS OF MEMORY
unsigned int pat[100];
int error_code(int err)
{


    if (err == 0)
    {
    	led_blue();
    	logger_error_code(err);   //IF ERROR CODE IS 0, PRINT OPERATION STARTED AND TURN BLUE LED
    								//RUN ON CONSOLE AND TERMINAL
        return	(printf("\n\r Operation Started \n\r"));
    }
    else if (err == 1)
    {
    	led_red();            //IF ERROR CODE IS 1, PRINT WARNING AND TURN RED LED
		                         //RUN ON CONSOLE AND TERMINAL
    	logger_error_code(err);

        return (printf("\n\r Warning: Buffer has not been allocated yet \n\r"));
    }
    else if (err == 2)
    {
    	led_red();          //IF ERROR CODE IS 2, PRINT MEMORY OUT OF BOUND AND TURN RED LED
								//RUN ON CONSOLE AND TERMINAL
    	logger_error_code(err);

        return	(printf("\n\r Memory Out of Bounds attempted - Exited with error code 2 \n\r"));
    }
    else if (err==3)
    {
    	led_red();           //IF ERROR CODE IS 3, PRINT ERROR ON VERIFYING AND TURN RED LED
		                            //RUN ON CONSOLE AND TERMINAL
    	logger_error_code(err);
        return (printf("\n\rERROR ON VERIFYING \n\r"));
    }
    else if (err==4)
    {
    	led_green();         //IF ERROR CODE IS 4, PRINT OPERATION SUCCESSFUL AND TURN GREEN LED
		                           //RUN ON CONSOLE AND TERMINAL
    	logger_error_code(err);
        return	(printf("\n\rOperation Successful \n\r"));
    }



}
uint32_t * allocate_words(unsigned int length)
{

    uint32_t *Block_Pointer;
    int i;                             //ALLOCATING MEMORY TO BLOCK POINTER 16 BYTES OF SPACE
    Block_Pointer = (uint32_t *)malloc(length*4);
    if (Block_Pointer!=NULL)
    {						    //IF BLOCK IS ALLOCATED PROPERLY, NO ERROR
        err=0;
        error_code(err);
    }
    else
    {
        err=2;                 //IF BUFFER IS OVER LIMIT,ERROR PRINT MEMORY BOUND EXCEEDED
        error_code(err);
    }


    for(i= 0; i<length; i++)
    											/*Initialize all memory blocks to 0*/
    {
        *(Block_Pointer+i)=0;
    }

    return (Block_Pointer);
}


void free_words(uint32_t *Block_Pointer,unsigned int length)
{
    int i;
    log_string(6);                 //PRINT  FREE MEMORY
    printf("\n\rFREE THE MEMORY\n\r");
    for (i=0; i<length; i++)     //CHECK IF MEMORY HAS BEEN SUCCESSFULLY ALLOCATED
    {
        if (Block_Pointer!=NULL) 	//IF YES FREE THE BLOCK AND INITIALIZE TO NULL
        {   free(Block_Pointer);
            Block_Pointer = NULL;
        }

        else
        {
        	err=1;                 //IF NO GIVE WARNING FREE THE BLOCK AND INITIALIZE TO NULL
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
    log_string(2);                        //DISPLAY THE MEMORY PATTERN STRING
    for(i=0; i<Data_words_to_read; i++)
    {									// PRINT THE VALUE AT THOSE ADDRESS

        printf("  Data at %p address is %x \n\r",(Block_Pointer) +i,Block_Pointer[i]);
    }

    log_data(Block_Pointer, Data_words_to_read); //PRINT IN UART
    return (Block_Pointer);
}

void write_memory(uint32_t * loc,uint8_t offset, uint32_t value)
{
    log_string(4);                       //WRITE MEMORY STRING PRINTED
    printf("\n\rWRITE DATA TO MEMORY\n\r");
    loc[0+offset] = value;          // A PARTICULAR VALUE IS WRITTEN TO THE LOCATION
}




void invert_block(uint32_t * loc, size_t length)
{
    int i,data,inverted;
    for(i=0; i<length; i++)       //INVERT THE ENTIRE BLOCK BY USING XOR OPERATION AND RUNNING
    								//FOR LOOP FROM START TO END
    {
        data=*(loc+i);
        inverted = 0xFFFFFFFF^data;
        									// Exor with 1 togges the bit
        *(loc+i) = inverted;
        printf(" inverted data at %p address is %08x \n\r",(loc+i),inverted);

        log_invert_block(loc,i,inverted); //PRINT THE INVERTED VALUE IN UART
    }

}
void invert(uint32_t * loc, size_t offset)
{
    int data,inverted;
    log_string(3);               //PRINTING STRING INVERT DATA
    printf("\n\rINVERT DATA OF A MEMORY LOCATION\n\r ");

    data=loc[offset];
    inverted = 0xFFFFFFFF^data;  //INVERTING THE PARTICULAR VALUE USING XOR

    loc[offset] = inverted;

    printf(" \n\rInverted data at %p address is %08x \n\r",(loc+offset),inverted);
    printf("\n\r");
    log_invert(loc,offset,inverted);   //PRINT THE INVERTED VALUE IN UART
}

uint32_t *  get_address(uint32_t * loc, int offset)
{
    log_get_address(loc,offset);         	//GET ADDRESS AT OFFSET FROM LOCATION
    printf("  Address at offset %d is %p \n\r",offset,loc+offset);
    return (loc+offset);

}

void write_pattern(uint32_t * loc, size_t length, int8_t seed)
{
    int i;
    gen_pattern(length, seed);   // CALL THE RANDOM PATTERN GENERATION FUNCTION
    printf("\n\r WRITE PATTERN TO MEMORY\n\r");
    log_string(1);              // PRINT THE STRING WRITRE PATTERN
    for (i=0; i<length; i++)
    {
        loc[i]=pat[i];        //WRITE RANDOM PATTERN VALUE TO THE BLOCK_POINTER
        printf("%p\n\r",loc[i]);
    }

}


uint32_t * verify_pattern(uint32_t * loc, size_t length, int8_t seed)
{
    int i;

    gen_pattern(length, seed);         // CALL THE RANDOM PATTERN GENERATION FUNCTION TO VERIFY

    log_string(5);               // PRINT VERIFY PATTERN STRING
    printf("\n\rVERIFYING RANDOM PATTERN TO MEMORY\n\r");
    for (i=0; i<length; i++)
    {
        block2[i]=pat[i];        // COPY THE RANDOM PATTERN INTO ARRAY BLOCK2

    }
    for (i=0; i<length; i++)
    {
        if(block2[i]==loc[i])     //VERIFY IF MEMORY PATTERN MATCHES PATTER AT THE LOCATION
        {
            LED_BLUE_OFF();
            LED_RED_OFF();
        }
        else
        {
            err=3;               //IF PATTERN DOES NOT MATCHG AT A LOCATION PRINT THE ADDRESS
            					//AND PARTICULAR VALUE AT THAT ADDRESS
            error_code(err);
            printf("\n\rAddress %p contains value %p\n\r",&loc[i],loc[i]);
            log_verify_pattern(loc,i);
            LED_BLUE_OFF();
            LED_RED_ON();
        }
    }

    return (loc);

}



