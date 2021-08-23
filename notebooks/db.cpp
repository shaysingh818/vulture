#include "db.h"


sqlite3* initDB(char* filename){

    sqlite3* DB; 
    int exit = 0; 
    exit = sqlite3_open("vulture.db", &DB); 
    if (exit) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(DB));
        return NULL;
    }
    else
        fprintf(stderr, "Opened database successfully\n");

    return DB; 

}


int checkDB(int result, sqlite3* DB, char *err_msg){

    if (result != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);        
        sqlite3_close(DB);
        return 0; 
    }

    return 1; 
    
}

void closeDB(sqlite3* DB){
    sqlite3_close(DB); 
}


