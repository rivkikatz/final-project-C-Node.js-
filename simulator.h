#pragma once
#include "camera.h"
class simulator
{
public:
	camera cameras[2];
	int numberOfCameras;
	simulator();
	~simulator();
	void run();
	int sendToServer();
	
};