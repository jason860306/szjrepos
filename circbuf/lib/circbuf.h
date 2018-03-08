/*****************************************************************************\
*                     CircBuf - Circular Buffer FIFO's                        *
*          --------------------------------------------------------           *
*                                                                             *
* Filename : circbuf.h                                                        *
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

#ifndef __CBUF_H_
#define __CBUF_H_

#ifdef DEBUG
#include <stdio.h>
#include <stdlib.h>
#endif

#include "types.h"

#define CB_READ_INP          0
#define CB_WRITE_INP         1
#define CB_BUF_READONLY      2
#define CB_BUF_WRITEONLY     3
#define CB_LASTIN            4
#define CB_ALLREAD           5

struct CircularBuffer {
	euint8* buf;
	euint8  status;
	euint32 numsectors;
	euint32 sectorsize;
	euint32 readPointer,writePointer;
};
typedef struct CircularBuffer CircularBuffer;

euint32 cb_ptrToSector(CircularBuffer *cb,euint8* ptr);
euint8* cb_sectorToPtr(CircularBuffer *cb,euint32 sector);
euint8  cb_getAttr    (CircularBuffer *cb,euint8 attribute);
void    cb_setAttr    (CircularBuffer *cb,euint8 attribute,euint8 val);

void    cb_init(CircularBuffer *cb, euint8* mem, euint32 numsectors, euint32 sectorsize);

euint8* cb_readPacket(CircularBuffer *cb);
void    cb_doneReadPacket(CircularBuffer *cb);
void cb_cancelReadPacket(CircularBuffer *cb);
euint8* cb_writePacket(CircularBuffer *cb);
void    cb_doneWritePacket(CircularBuffer *cb);
void cb_cancelWritePacket(CircularBuffer *cb);

void    cb_lastPacketIsIn(CircularBuffer *cb);
euint8  cb_moreComing(CircularBuffer *cb);
void    cb_lastPacketIsOut(CircularBuffer *cb);
euint8  cb_readyReading(CircularBuffer *cb);

#ifdef DEBUG
void    cb_printStatus(CircularBuffer *cb);
#endif

#endif
