#ifndef DB_H
#define DB_H

#include <sqlite3.h> 
#include <stdio.h> 

#define DB_FILE "vulture.db"

sqlite3* initDB(char* filename);
int checkDB(int result, sqlite3* DB, char* err_msg);  
void closeDB(sqlite3* DB); 

#endif
