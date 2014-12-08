#ifndef _buffer_h
#define _buffer_h

#include <sys/shm.h>

struct buffer_struct
{
	char letter;
	int size;
};

	
typedef struct buffer_struct Buffer;

void push_buffer(Buffer*, char a);

void init_buffer(Buffer* buf);

bool empty_buffer(Buffer *buf);
#endif
