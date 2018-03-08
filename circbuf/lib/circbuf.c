/*****************************************************************************\
*                     CircBuf - Circular Buffer FIFO's                        *
*          --------------------------------------------------------           *
*                                                                             *
* Filename : circbuf.c                                                        *
*                                                                             *
* This program is free software; you can redistribute it and/or               *
* modify it under the terms of the GNU General Public License                 *
* as published by the Free Software Foundation; version 3                     *
* of the License.                                                             *
                                                                              *
* This program is distributed in the hope that it will be useful,             *
* but WITHOUT ANY WARRANTY; without even the implied warranty of              *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
* GNU General Public License for more details.                                *
*                                                                             *
* As a special exception, if other files instantiate templates or             *
* use macros or inline functions from this file, or you compile this          *
* file and link it with other works to produce a work based on this file,     *
* this file does not by itself cause the resulting work to be covered         *
* by the GNU General Public License. However the source code for this         *
* file must still be made available in accordance with section (3) of         *
* the GNU General Public License.                                             *
*                                                                             *
* This exception does not invalidate any other reasons why a work based       *
* on this file might be covered by the GNU General Public License.            *
*                                                                             *
*                                                    (c)2007 Lennart Yseboodt *
\*****************************************************************************/

#include "circbuf.h"

euint32 cb_ptrToSector(CircularBuffer *cb,euint8* ptr)
{
	return((ptr-(cb->buf))/(cb->sectorsize));
}

euint8* cb_sectorToPtr(CircularBuffer *cb,euint32 sector)
{
	return(cb->buf+(sector*(cb->sectorsize)));
}

euint8 cb_getAttr(CircularBuffer *cb,euint8 attribute)
{
	return(cb->status&(1<<attribute));
}

void cb_setAttr(CircularBuffer *cb,euint8 attribute,euint8 val)
{
	if(val){
		cb->status|=1<<attribute;
	}else{
		cb->status&=~(1<<attribute);
	}
}

void cb_init(CircularBuffer *cb, euint8* mem, euint32 numsectors, euint32 sectorsize)
{
	cb->buf = mem;
	cb->numsectors = numsectors;
	cb->sectorsize = sectorsize;
	cb->status = 0;
	cb->readPointer = 0;
	cb->writePointer = 0;
	cb_setAttr(cb,CB_BUF_WRITEONLY,1);
}

euint8* cb_readPacket(CircularBuffer *cb)
{
	if((cb->readPointer == cb->writePointer)&&(!cb_getAttr(cb,CB_BUF_READONLY)))return(0);
	if(cb_getAttr(cb,CB_READ_INP))return(0);
	cb_setAttr(cb,CB_READ_INP,1);
	return(cb_sectorToPtr(cb,cb->readPointer));
}

void cb_doneReadPacket(CircularBuffer *cb)
{
	if(!cb_getAttr(cb,CB_READ_INP))return;
	if(cb_getAttr(cb,CB_BUF_READONLY))cb_setAttr(cb,CB_BUF_READONLY,0);
	if(cb->readPointer+1 == cb->numsectors){
		cb->readPointer=0;
	}else{
		cb->readPointer++;
	}
	if(cb->readPointer == cb->writePointer)cb_setAttr(cb,CB_BUF_WRITEONLY,1);	
	cb_setAttr(cb,CB_READ_INP,0);	
}

void cb_cancelReadPacket(CircularBuffer *cb)
{
	if(!cb_getAttr(cb,CB_READ_INP))return;
	cb_setAttr(cb,CB_READ_INP,0);	
}

euint8* cb_writePacket(CircularBuffer *cb)
{
	if((cb->readPointer == cb->writePointer)&&(!cb_getAttr(cb,CB_BUF_WRITEONLY)))return(0);
	if(cb_getAttr(cb,CB_WRITE_INP))return(0);
	cb_setAttr(cb,CB_WRITE_INP,1);
	return(cb_sectorToPtr(cb,cb->writePointer));
}

void cb_doneWritePacket(CircularBuffer *cb)
{
	if(!cb_getAttr(cb,CB_WRITE_INP))return;
	if(cb_getAttr(cb,CB_BUF_WRITEONLY))cb_setAttr(cb,CB_BUF_WRITEONLY,0);
	if(cb->writePointer+1 == cb->numsectors){
		cb->writePointer=0;
	}else{
		cb->writePointer++;
	}
	if(cb->readPointer == cb->writePointer)cb_setAttr(cb,CB_BUF_READONLY,1);
	cb_setAttr(cb,CB_WRITE_INP,0);	
}

void cb_cancelWritePacket(CircularBuffer *cb)
{
	if(!cb_getAttr(cb,CB_WRITE_INP))return;
	cb_setAttr(cb,CB_WRITE_INP,0);	
}

void cb_lastPacketIsIn(CircularBuffer *cb)
{
	cb_setAttr(cb,CB_LASTIN,1);
}

euint8 cb_moreComing(CircularBuffer *cb)
{
	return((cb_getAttr(cb,CB_LASTIN))?0:1);
}

void cb_lastPacketIsOut(CircularBuffer *cb)
{
	cb_setAttr(cb,CB_ALLREAD,1);
}

euint8 cb_readyReading(CircularBuffer *cb)
{
	return((cb_getAttr(cb,CB_ALLREAD))?1:0);
}

#ifdef DEBUG
void cb_printStatus(CircularBuffer *cb)
{
	euint8 c;

	printf("BUF READONLY      : %i\n"
		   "BUF WRITEONLY     : %i\n"
           "READ  IN PROGRESS : %i\n"
           "WRITE IN PROGRESS : %i\n",
	cb_getAttr(cb,CB_BUF_READONLY)?1:0,
	cb_getAttr(cb,CB_BUF_WRITEONLY)?1:0,
	cb_getAttr(cb,CB_READ_INP )?1:0,
	cb_getAttr(cb,CB_WRITE_INP)?1:0);

	for(c = 0 ; c < cb->numsectors ; c++){
		printf("%2.2i  ",c);
	}printf("\n");
	for(c = 0 ; c < cb->numsectors ; c++){
		if(cb->readPointer == c){
			if(cb_getAttr(cb,CB_READ_INP)){
				printf("^=Ri");
			}else{
				printf("^=Rp");
			}
		}else{
			printf("    ");
		}
	}printf("\n");
	for(c = 0 ; c < cb->numsectors ; c++){
		if(cb->writePointer == c){
			if(cb_getAttr(cb,CB_WRITE_INP)){
				printf("^=Wi");
			}else{
				printf("^=Wp");
			}
		}else{
			printf("    ");
		}
	}printf("\n");
	
}
#endif
