#include "buffer.h"

#include <stdio.h>
#include <stdlib.h>

#include <sys/shm.h>
#include <sys/stat.h>

void push_buffer(Buffer* buf, char c)
{          
    // if(empty_buffer())     
    // {
      // fprintf(stderr, "push_buffer: buffer is full");
      // return;
    // }
       
     buf->letter = c;
     buf->size++;
}

void init_buffer(Buffer* buf)
{
	buf->letter = '\0';	
	buf->size = 0;
}

bool empty_buffer(Buffer* buf)
{
	if(buf->size)
		return false;

	return true;
}
