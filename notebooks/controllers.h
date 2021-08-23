#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <sqlite3.h> 
#include <stdio.h> 


/**
    
    Library for interacting with SQL database
    Created CRUD OPERATIONS
    

*/


static int callback(void *data, int argc, char **argv, char **azColName);
int viewClients(sqlite3* DB);
int createClient(sqlite3* DB, char* ipAddress);
int updateClient(sqlite3* DB, char* ipAddress, char* newValue); 
int deleteClient(sqlite3* DB, char* ipAddress); 

#endif

