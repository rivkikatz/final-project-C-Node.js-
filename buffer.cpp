#include "buffer.h"
#include <Windows.h>
#include <iostream>


buffer::buffer()
{
	buffers = nullptr;
	index = 0;
}

buffer::~buffer()
{
	free(buffers);
}

void buffer::addToBuffer(unsigned char* message)
{
	buffers = (unsigned char**)realloc(buffers, sizeof(unsigned char*) * (index + 1));
	buffers[index] = message;
	index++;
}

unsigned char** buffer::getBuffer()
{
	return buffers;
}

void buffer::cleanBuffer()
{
	buffers = nullptr;
}

int buffer::getIndex()
{
	return index;
}



