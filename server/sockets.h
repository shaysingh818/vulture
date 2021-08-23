#ifndef SERVER_H
#define SERVER_H

#include <iostream> 
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

// constants
#define BUFFER_LENGTH 1024
#define DEFAULT_PORT "8888" 
#define SERVER_IP "192.168.0.15"
#pragma comment(lib,"ws2_32.lib")

// library functions
struct addrinfo GetSocketAddress(char* host, const char* port); 
int createAndBind(struct addrinfo *result); 
void listenSocket(int *myconnection); 

#endif
