
#include "logger.h"

int log_enable=1;
int log_disable=0;
int status=0;
int log_status(int status)
{
	if (status==log_enable)
	{
		//PRINTF("\n\rLOGGER IS ON\n\r");
		return (status);
	}
	else
	{
			//PRINTF("\n\rLOGGER IS OFF\n\r");
			return (status);
	}
}


//log_status(log_enable);
void log_data(uint32_t * Block_Pointer,uint8_t length)
{
	if (log_status(status))
	{


    int i;
    for(i=0; i<length; i++)
    {
        PRINTF("  DATA AT %p ADDRESS IS %02x \n\r",(Block_Pointer) +i,Block_Pointer[i]);

    }
	}

}






void log_get_address(uint32_t * loc, int offset)
{
	if (log_status(status))
	{

    PRINTF("  ADDRESS AT OFFSET %d is %p \n\r",offset,loc+offset);
	}
}

void log_invert(uint32_t * loc, int offset, uint32_t inverted)
{
	if (log_status(status))
	{

    PRINTF(" inverted data at %p address is %08x \n\r",(loc+offset),inverted);
	}
}

void log_invert_block(uint32_t * loc,uint8_t i,uint32_t inverted)
{
	if (log_status(status))
	{
    PRINTF(" inverted data at %p address is %08x \n\r",(loc+i),inverted);
	}

}



void log_verify_pattern(uint32_t * loc,uint8_t i)
{
	if (log_status(status))
	{
    PRINTF("\n\rAddress %p contains value %p\n\r",&loc[i],loc[i]);
	}
}

void log_free_memory()
{
	if (log_status(status))
	{
    PRINTF("\n\rFREE THE MEMORY\n\r");
	}
}

void log_string(uint8_t string)
{
	if (log_status(status))
	{
    if (string==1)
        PRINTF("\n\r WRITE PATTERN TO MEMORY\n\r");
    else if (string==2)
        PRINTF("\n\r DISPLAY MEMORY PATTERN\n\r");
    else if (string==3)
        PRINTF("\n\rINVERT DATA OF A MEMORY LOCATION\n\r ");
    else if (string==4)
        PRINTF("\n\rWRITE DATA TO MEMORY\n\r");
    else if (string==5)
        PRINTF("\n\rVERIFYING RANDOM PATTERN TO MEMORY\n\r");
	}

}
int logger_error_code(int log_err)
{
	if (log_status(status))
	{
	    if (log_err == 0)
	        return	(PRINTF("\n\r Operation Completed \n\r"));
	    else if (log_err  == 1)
	        return (PRINTF("\n\r Warning: Buffer has not been allocated yet \n\r"));
	    else if (log_err  == 2)
	        return	(PRINTF("\n\r Memory Out of Bounds attempted - Exited with error code 2 \n\r"));
	    else if (log_err ==3)
	        return (PRINTF("\n\rERROR ON VERIFYING \n\r"));
	    else
	        return	(PRINTF("\n\rOperation Ssuccessful \n\r"));



	}
}




