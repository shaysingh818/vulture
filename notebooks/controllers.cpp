#include "db.h"
#include "controllers.h"


static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   
   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   return 0;
}


int viewClients(sqlite3* DB){
    
    char str[200];
    int id = 1; 
    char *err_msg = 0;
    const char* data = "Callback function called";

    sprintf(str, "SELECT * FROM CLIENT;"); 
 
    int result = sqlite3_exec(DB, str, callback, (void*)data, &err_msg);

    if(checkDB(result, DB, err_msg)){
        return 1; 
    }

    return 0; 
    
}

int createClient(sqlite3* DB, char* ipAddress){
    
    char str[200];
    int id = 1; 
    char *err_msg = 0;

    sprintf(str, "INSERT INTO CLIENT (IP_ADDRESS) VALUES('%s');", ipAddress);  

    printf("Insert Statement: %s \n", str);

    int result = sqlite3_exec(DB, str, 0, 0, &err_msg);
 
    if(checkDB(result, DB, err_msg)){
        return 1; 
    }


    return 1; 

}

int updateClient(sqlite3* DB, char* ipAddress, char* newValue){
    
    char str[200];
    int id = 1; 
    char *err_msg = 0;

    sprintf(str, "UPDATE CLIENT SET IP_ADDRESS='%s' WHERE IP_ADDRESS='%s';", newValue,ipAddress);  

    printf("Update Statement: %s \n", str);

    int result = sqlite3_exec(DB, str, 0, 0, &err_msg);

     
    if(checkDB(result, DB, err_msg)){
        return 1; 
    }


    return 1; 

}

int deleteClient(sqlite3* DB, char* ipAddress){
    
    char str[200];
    int id = 1; 
    char *err_msg = 0;

    sprintf(str, "DELETE FROM CLIENT WHERE IP_ADDRESS='%s';", ipAddress);  

    printf("Delete Statement: %s \n", str);

    int result = sqlite3_exec(DB, str, 0, 0, &err_msg);

     
    if(checkDB(result, DB, err_msg)){
        return 1; 
    }

    return 1; 
}




