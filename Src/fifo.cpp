#include "fifo.hpp"
#include <iostream>

Fifo::Fifo(unsigned int capacity)
	: qCapacity(capacity)
{
}

bool Fifo::push(const int& i)
{
	if(fifoQ.size() >= qCapacity) {
		return false;
	}
	fifoQ.push(i);
	return true;
}


int Fifo::pop()
{
	int retVal = fifoQ.front();
	fifoQ.pop();
	return retVal;
}
