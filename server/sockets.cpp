#include "sockets.h"

struct addrinfo GetSocketAddress(char* host, const char* port){
  /**
    Params:
        hints - Addrinfo structure for setting up socket later. 

    Setting up the addrinfo for the socket. Can choose TCP or UDP protocol. 
  */

  struct addrinfo hints, *result = NULL; 

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  int iResult = getaddrinfo(host, port, &hints, &result);
  if ( iResult != 0 ) {
      printf("getaddrinfo failed with error: %d\n", iResult);
  }

  return *result; 
}


int createAndBind(struct addrinfo *result){
  /**
    Params:
        connectSocket - Windows socket. 
        *result - addrinfo structure that was set up previously 

    Purpose:
        Resolving server address and port for connecting
        Check if connection was successful
  */
  int connectSocket = -1; 

  // Create a SOCKET for connecting to server
  connectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
  if (connectSocket == -1) {
    perror("Socket create failed"); 
    freeaddrinfo(result);
    return 1;
  }

  // Setup the TCP listening socket
  int iResult = bind(connectSocket, result->ai_addr, (int)result->ai_addrlen);
  if (iResult == -1) {
    perror("bind failed"); 
    freeaddrinfo(result);
    close(connectSocket);
    return 1;
  }
 
  return connectSocket; 
}


void listenSocket(int *myconnection ){
  int iResult = listen(*myconnection, 5);
  if (iResult == -1) {
      perror("listen failed"); 
      close(*myconnection);
      //return NULL;
  }
}


