/* This is a simple demonstration program for CircBuf */

/* In an infinite loop it reads a character, puts it in the fifo, gets it from the fifo, and then echoes it back */

#include <stdio.h>

#include "circbuf.h"

int main()
{
	CircularBuffer cb;
	euint8 buffer[5]; /* 5 places in the FIFO */
	euint8 *fifomem;

	cb_init(&cb, buffer, 5, 1); /* Setup FIFO
				     * cb = CircularBuffer object
				     * buffer = buffer memory, you must allocate it
				     * 5, we have 5 slots...
				     * ... of 1 byte size */

	/* We start the loop */

	while(1){
		/* First, get room for the byte */
		fifomem = cb_writePacket(&cb);
		if(fifomem==0)return(0); /* If no space is available, we bail out */
		*fifomem=fgetc(stdin); /* Write the byte from stdin */
		cb_doneWritePacket(&cb); /* We indicate we are done writing */

		/* Now, we retrieve the byte */
		fifomem = cb_readPacket(&cb);
		if(fifomem==0)return(0); /* If there is no data, we bail out */
		fprintf(stdout,"%c",*fifomem); /* Echo the byte back */
		cb_doneReadPacket(&cb); /* We indicate we are done reading */
	}
}
