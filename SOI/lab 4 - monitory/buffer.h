#ifndef _buffer_h
#define _buffer_h

#include <sys/shm.h>
#include "monitor.h"

class Buffer : public Monitor
{
private:
	char letter;
	int size;
	int ilosc_czytelnikow;
	Monitor MoznaCzytac;

public:
	Buffer() : letter('\0'), size(0), ilosc_czytelnikow(0) {}
	void Producent(char);
	void Konsument(char);
	void push_buffer(char);
	bool empty_buffer();

};

#endif
