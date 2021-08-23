#ifndef CLIENT_H
#define CLIENT_H


#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mstcpip.h>
#include <ws2ipdef.h>
#include <string.h> 
#include <windows.h>

// macros
#define BUFFER_LENGTH 1024
#define DEFAULT_PORT "8888" 
#define SERVER_IP "10.0.0.41"
#pragma comment(lib,"ws2_32.lib")

// socket functions
bool startWinSock();
struct addrinfo GetSocketAddress(char* host, char* port); 


#endif
