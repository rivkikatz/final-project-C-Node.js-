#include "discoverMessage.h"
#include <cstring>
#include <stdlib.h>
#include <iostream>

void discoverMessage::parseMessage()
{
	if (!this->messageBuffer) {
		return;
	}

	std::memcpy(&(this->messageType), this->messageBuffer, 2);
	std::memcpy(&(this->distance), this->messageBuffer + 2, 4);
	std::memcpy(&(this->angle), this->messageBuffer + 6, 4);
	std::memcpy(&(this->speed), this->messageBuffer + 10, 4);


	//messageBuffer =(unsigned char*) realloc(messageBuffer,(sizeof(unsigned char) * 14));
	//	std::memcpy( this->messageBuffer,&(this->messageType), 2);
	//	std::memcpy( this->messageBuffer + 2,&(this->distance), 4);
	//	std::memcpy( this->messageBuffer + 6,&(this->angle), 4);
	//	std::memcpy( this->messageBuffer + 10,&(this->speed), 4);
	//	std::cout << "parsseddddddddddd\n";
	//	for (int i = 0; i < 14; i++)
	//	{
	//		std::cout << (int)messageBuffer[i];
	//	}
	//	std::cout << "\n";

}

void discoverMessage::parseBack()
{
	this->messageBuffer = (unsigned char*)malloc(14);
	std::memcpy(this->messageBuffer, &(this->messageType), 2);
	std::memcpy(this->messageBuffer + 2, &(this->messageId), 2);
	std::memcpy(this->messageBuffer + 4, &(this->distance), 4);
	std::memcpy(this->messageBuffer + 8, &(this->angle), 4);
	std::memcpy(this->messageBuffer + 12, &(this->speed), 4);
	/*std::cout << "im discover parse back " << this->messageBuffer << "\n";

	for (int i = 0; i < 14; i++)
	{
		std::cout << messageBuffer[i];
	}
	std::cout << "\n";*/
}

void discoverMessage::print()
{
	std::cout << "----information about your messege:----" << "\n";
	std::cout << "Type:	" << this->messageType << "\t" << "Distance:	" << this->distance << "\t" << "Angle:	" << this->angle << "\t" << "Speed:	" << this->speed << "\n";
}

discoverMessage::discoverMessage(int messageId, int messageType, float distance, float angle, float speed) :baseMessage(messageId, messageType)
{
	this->distance = (distance < 500 || distance>10000) ? 0 : distance;
	this->angle = (angle < 0 || angle>360) ? 0 : angle;
	this->speed = (speed < 0 || speed>1000) ? 0 : speed;
}