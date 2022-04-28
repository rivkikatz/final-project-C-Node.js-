#pragma once
#include "baseMessage.h"
#include "buffer.h"

class camera
{	
public:
	char id;
	baseMessage** messages;
	buffer buffer;
	bool isActive;
	int messagesPerSecond;
	int messageIndex;

	camera();
	camera(char id);
	~camera();
	void generate();
	void sendToBuffer();
	void run();
	void stop();
	void printInfo();

};

