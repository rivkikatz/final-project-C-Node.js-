#include "camera.h"
#include "baseMessage.h"
#include "statusMessage.h"
#include "discoverMessage.h"
#include <random>
#include <Windows.h>
#include <iostream>

using namespace std;



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
		messages[messageIndex-1]->print();

		sendToBuffer();
		//sendToServer();
		Sleep(30000);

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

int camera::sendToServer()
{
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) {
		cout << "Winsock Connection Failed!" << endl;
		/*exit(1);*/
		return(1);
	}

	SOCKADDR_IN addr;
	int addrLen = sizeof(addr);
	IN_ADDR ipvalue;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");//loclahost
	addr.sin_port = htons(3030);
	addr.sin_family = AF_INET;

	SOCKET connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(connection, (SOCKADDR*)&addr, addrLen) == 0) {

		//string m = "you";
		string m;

		for (int i = 0; i < buffer.getIndex(); i++)
		{
			cout << buffer.getBuffer()[i];
			m =(char*) buffer.getBuffer()[i];
			send(connection, m.c_str(), m.length(), 0);
			Sleep(3000);
		}
		//m = (char*)buffer.getBuffer();


		cout <<" Connected!" << endl;

		//send(connection, b.c_str(), b.length(), 0);
		
		//char buf[] = { (char)buffer.getBuffer()[0] };
	
		/*if (!m.empty()) {
			cout << m;
			send(connection, m.c_str(), m.length(), 0);
			buffer.cleanBuffer();
		}*/

		//send(connection,arr, sizeof(arr), 0);
		/*if (send(connection, b.c_str(), b.length(), 0)==0) {
			closesocket(connection);
			WSACleanup();
		}*/
		//exit(0);
		return(1);

	}
	else {
		cout << "Error Connecting to Host" << endl;
		//exit(1);
		return(1);
	}
	return 0;
}

