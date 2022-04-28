#include "camera.h"
#include "baseMessage.h"
#include "statusMessage.h"
#include "discoverMessage.h"
#include <random>
#include <Windows.h>
#include <iostream>


camera::camera() {
	std::cout << "empty constructor\n";
	isActive = true;
	messageIndex = 0;
	messagesPerSecond = 3;
	messages = nullptr;
}

camera::camera(char id) {
	std::cout << "full constructor id="<<id<<"\n";
	this->id = id;
	isActive = true;
	messageIndex = 0;
	messagesPerSecond = 3;
	messages = nullptr;
}

camera::~camera() {
	free(messages);
}

statusMessage* createStatusMessage()
{
	static int id = 1;
	id++;
	statusMessage* sm = new statusMessage(id, 1, rand() % 3 + 1);
	return sm;
}

discoverMessage* createDiscoverMessage()
{
	static int id = 100;
	id++;
	discoverMessage* dm = new discoverMessage(id, 2, rand() % 9500 + 500, rand() % 361, rand() % 1001);
	return dm;
}

void camera::generate()
{	
	int amount = rand()%5+1;
	messages = (baseMessage**) realloc(messages, sizeof(baseMessage*) * (messageIndex + amount));
	for (int i = 0; i < amount; i++)
	{
		(rand() % 2 + 1 == 1) ? (messages[messageIndex] = createStatusMessage()) : (messages[messageIndex] = createDiscoverMessage());
		this->messageIndex++;
		
	}
}
void camera::sendToBuffer() {
	for (int i = 0; i < messageIndex; i++)
	{
		messages[i]->parseBack();
		buffer.addToBuffer(messages[i]->getMessageBuffer());
	}
	std::cout << this->buffer.getBuffer()<<std::endl;
	free(messages);
	messages = nullptr;
	messageIndex = 0;
}

void camera::run()
{
	
	while (isActive) {
		/*std::cout << "camera no "<<id<<std::endl;*/
		generate();
		std::cout<<"camera id= "<<this->id << ", num of messages  " << messageIndex << "---------------\n";
		//messages[messageIndex-1]->print();

		sendToBuffer();

		Sleep(1000);
	}	
}

void camera::stop()
{
	isActive = false;
}

void camera::printInfo()
{
	std::cout << "id= " << this->id << ", isActive= " << isActive << ", messagesPerSecond= " << messagesPerSecond <<", messageIndex= " << messageIndex<<"\n";
}
