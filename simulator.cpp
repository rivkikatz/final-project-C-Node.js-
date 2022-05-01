#include "Simulator.h"
#include <iostream>
#include <thread>
#include <Windows.h>

//#include "stdafx.h"





simulator::simulator()
{
	//std::ifstream config_file("config.json", std::ifstream::binary);
	//std::cout << config_file;

	numberOfCameras = 2;
	char ids = 'a';
	for (int i = 0; i < numberOfCameras; i++) {
		cameras[i] = camera(ids++);
	}
}

simulator::~simulator()
{

}


void simulator::run()
{
	std::thread camerasThreads[2];
	//std::cout<<"to stop a camera press E"<<std::endl;

	for (int i = 0; i < numberOfCameras; i++) {
		camerasThreads[i] = std::thread(&camera::run, &cameras[i]);
	}
	
	while (true) {
		for (int i = 0; i < numberOfCameras; i++) {
			//cameras[i].buffer.getBuffer()[0- cameras[i].buffer.getIndex()];//send to server

			/*for (int j = 0; j < cameras[i].buffer.getIndex(); j++)
			{
				sendToServer(cameras[i].buffer.getBuffer()[j]);
			}*/
			//std::cout << "camera number " << i <<",messageIndex "<< cameras[i].messageIndex<< "\n";

			/*for (int j = 0; j < cameras[i].messageIndex; j++)
			{
				std::cout << "camera number " << i << "message number" << j << "\n";
				cameras[i].messages[j]->print();
				cameras[i].messages[j]->parseMessage();
				cameras[i].messages[j]->print();
				Sleep(2000);

			}*/
			cameras[i].sendToServer();
			
		}
		Sleep(5000);
	}

	std::cout << "\n";
}




