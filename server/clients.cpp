#include "clients.h"
#include "sockets.h"

const char* inet_ntop(int family, const void *addrptr, char *strptr, size_t len){

    const u_char *p = (const u_char *) addrptr;

    if (family == AF_INET) {
        char    temp[INET_ADDRSTRLEN];

        snprintf(temp, sizeof(temp), "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
        if (strlen(temp) >= len) {
            errno = ENOSPC;
            return (NULL);
        }
        strcpy(strptr, temp);
        return (strptr);
    }
    errno = EAFNOSUPPORT;
    return (NULL);
}


int acceptClient(int serverSock, client_t *client){

    socklen_t sin_size = sizeof client->addr; 
    client->cs = accept(serverSock, (sockaddr*)&client->addr, &sin_size);

    if (client->cs == -1) {
        perror("accpet failed with error");
        close(serverSock);
        return 0;
    }

    client->con = true;
    cout << "Client connected " << endl; 

    FD_ZERO(&client->set);
	FD_SET(client->cs,&client->set);

    return 1; 

}

void recvClient(client_t *client){
    char data[45]; // current size for our packet
    int recvResult; 
    do {
      recvResult = recv(client->cs, data, 52, 0); 
      if(recvResult > 0){
          printf("Bytes received: %d\n", recvResult);
          printf("%s \n ",data);
      }else if(recvResult == 0){
          printf("Connection closing...\n");
      }else{
          perror("recv failed with error"); 
          close(client->cs);
      }
    }while(recvResult > 0); 
    //delete data; 
}

// create method for printing out client information
void * handleClientConnection(void* p_client){

    client_t client = *((client_t*)p_client);
    free(p_client);  
    char str[255];
    inet_ntop(AF_INET, &(client.addr.ss_family), str, 255);
    //cout << "Client address: " << str << endl; 
    client.con = true; 

    cout << "Connection status: " << client.con << endl;
    cout << "Address " << str << endl; 
    //cout << "Client port: " << htons(client.addr.sin_port) << endl; 

    recvClient(&client); 

    return NULL; 
}


