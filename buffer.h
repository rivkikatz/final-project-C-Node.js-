#pragma once
class buffer
{
private:
	unsigned char** buffers;
	int index;
public:
	buffer();
	~buffer();
	void addToBuffer(unsigned char* message);
	unsigned char** getBuffer();
	void cleanBuffer();
	int getIndex();
};

