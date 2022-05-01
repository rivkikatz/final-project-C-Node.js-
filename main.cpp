

#include <iostream>
#include "simulator.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "Ws2_32.lib")
#include <string.h>
#include <sstream>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;
int main()
{  
    simulator s=simulator();
    s.run();
}


