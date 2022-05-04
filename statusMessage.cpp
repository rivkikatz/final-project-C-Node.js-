#include "statusMessage.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

void statusMessage::parseMessage()//from buffer to variables
{
	if (!this->messageBuffer)
		return;

	std::memcpy(&(this->messageType), this->messageBuffer, sizeof(int));
	std::memcpy(&(this->status), this->messageBuffer + sizeof(int), sizeof(short));


	/*messageBuffer = (unsigned char*)realloc(messageBuffer, (sizeof(unsigned char) * 3));

	std::memcpy( this->messageBuffer, & (this->messageType) , 2);
	std::memcpy( this->messageBuffer + 2,&(this->status), 1);*/
	/*std::cout << "parsseddddddddddd\n";
	for (int i = 0; i < 3; i++)
	{
		std::cout << (int)messageBuffer[i] ;
	}
	std::cout << "\n";*/


}

void statusMessage::parseBack()//from variables to buffer
{
	this->messageBuffer = (unsigned char*)malloc(5);
	std::memcpy(this->messageBuffer, &(this->messageType), 2);
	std::memcpy(this->messageBuffer + 2, &(this->messageId), 2);
	std::memcpy(this->messageBuffer + 4, &(this->status), 1);
	/*std::cout << "im status parse back " << this->messageBuffer << "\n";
	for (int i = 0; i < 5; i++)
	{
		std::cout << messageBuffer[i];
	}
	std::cout << "\n";*/
}

void statusMessage::print()
{
	std::cout << "inform about your messege:" << "\n";
	std::cout << "Id: " << this->messageId << " Type:	" << this->messageType << "\t" << "Status:	" << this->status << "\n";
}

statusMessage::statusMessage(int messageId, int messageType, short status) :baseMessage(messageId, messageType)
{
	this->status = (status < 1 || status>3) ? 0 : status;
}
