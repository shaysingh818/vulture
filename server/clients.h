#ifndef CLIENTS_H
#define CLIENTS_H

#include <iostream> 
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>


using namespace std; 

struct client_t {
	bool con;			//Set true if a client is connected
	sockaddr_storage addr;	//Client info like ip address
	int cs;		//Client socket
	fd_set set;			//used to check if there is data in the socket
	int i;				//any piece of additional info
};

int acceptClient(int serverSock, client_t *client); 
void recvClient(client_t *client); 
void * handleClientConnection(void* p_client);

#endif
