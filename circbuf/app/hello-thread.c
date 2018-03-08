/* This is a simple threaded demonstration program for CircBuf */

/* Two threads are running, one will contineuously get data from stdin and put it in the FIFO,
   a second thread will read that data back and echo it to stdout */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <curses.h>

#include "circbuf.h"

void* reading_thread(void *x);
void* writing_thread(void *x);

CircularBuffer cb;
euint8 buffer[5]; /* 5 places in the FIFO */

int main()
{
	pthread_t rthread,wthread;
	int x;

	/* Initialise the fifo */
	cb_init(&cb, buffer, 5, 1);

	initscr();
	cbreak();
	noecho();

	/* Create the threads */
	rthread = pthread_create(&rthread, NULL, reading_thread, NULL);
	wthread = pthread_create(&wthread, NULL, writing_thread, NULL);

	/* Wait forever for completion */
	while(1)sleep(1);

	return(0);	
}

void* reading_thread(void *x)
{
	euint8* fifomem;
	int key;

	while(1){
		while( (fifomem = cb_writePacket(&cb))==0 )sleep(1);
		key = getch();
		if(key==KEY_ENTER){
			endwin();
			exit(0);
		}
		*fifomem = key;
		cb_doneWritePacket(&cb);
	}
}

void* writing_thread(void *x)
{
	euint8 c;
	euint8* fifomem;

	while(1){
		while( (fifomem = cb_readPacket(&cb))==0 )sleep(1);
		c = *fifomem;
		cb_doneReadPacket(&cb);
		printw("%c",c);refresh();
	}
}
