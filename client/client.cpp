#include "client.h"

/**
  This file is for testing scalable socket functions that can be written for the client. 
*/


bool startWinSock(){
 	WSADATA wsaData; 
	int iResult;
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return false;
	}
	return true; 
}


struct addrinfo GetSocketAddress(char* host, char* port){
	struct addrinfo hints, *result = NULL;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (getaddrinfo(host, port, &hints, &result) != 0){
		printf("Get addr info failed ");
		WSACleanup(); 
	}
	return *result; 
}

