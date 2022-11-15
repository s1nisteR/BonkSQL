#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"
#include "crow/crow_all.h"

static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;

    for(i = 0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}



int main()
{
    /*

    sqlite3* db;
    char* zErrMsg = nullptr;
    int rc;

    rc = sqlite3_open("test.db", &db);
    if(rc)
    {
        std::cout << "Could not open the database" << std::endl;
    }
    else
    {
        std::cout << "Opened the database successfully" << std::endl;
    }

    //example query
    std::string query = "SELECT * FROM Company";
    rc = sqlite3_exec(db, query.c_str(), callback, nullptr, &zErrMsg);
    if(rc != SQLITE_OK)
    {
        std::cout << zErrMsg << std::endl;
        std::cout << "There was an error in the SQL statement!" << std::endl;
    }

    sqlite3_close(db);
     */

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    app.port(8080).multithreaded().run();
    return 0;
}
