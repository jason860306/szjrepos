/* This is a simple demonstration program for CircBuf */

/* This program puts the numbers 0, 1 and 2 on a FIFO and reads them back */

#include <stdio.h>

#include "circbuf.h"

int main()
{
	CircularBuffer cb;
	euint8 buffer[40]; /* 10 places of size 4 */
	euint32 *d,c;

	/* Init */	
	cb_init(&cb, buffer, 10, 4); 

	/* Put values */
	for(c=0;c<3;c++){
		d = (euint32*)cb_writePacket(&cb); if(d==0)return(-1);
		*d=c;
		cb_doneWritePacket(&cb);
	}
	
	for(c=0;c<3;c++){
		d = (euint32*)cb_readPacket(&cb); if(d==0)return(-1);
		printf("%d\n",*d);
		cb_doneReadPacket(&cb);
	}
}
