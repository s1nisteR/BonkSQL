//
// Created by sinister on 11/16/22.
//

#include "db.h"

json tempQueryResponse;
long long counter = -1;

static int callback(void *data, int argc, char **argv, char **azColName)
{
    counter++;
    int i;

    for(i = 0; i<argc; i++){
        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        tempQueryResponse[counter][azColName[i]] = argv[i] ? argv[i] : "NULL";
    }
    return 0;
}

db::db(const std::string& t_dbName)
{
    m_dbName = t_dbName;
    m_rc = sqlite3_open(":memory:", &m_db);
    if(m_rc)
    {
        std::cout << "Could not open the database!" << std::endl;
    }
    else
    {
        std::cout << "Opened the database successfully!" << std::endl;
    }
    int status = this->initializeDB(); //intialize the newly created in memory database
    switch(status)
    {
        case 0:
            std::cout << "[OK]In-memory database was loaded from persistent backup!" << std::endl;
            break;
        case 1:
            std::cout << "[ERROR]There was an error when loading the persistent backup!" << std::endl;
            break;
        case -1:
            std::cout << "[OK]Persistent backup does not exist yet, creating an empty in-memory database!" << std::endl;
            break;
        default:
            std::cout << "[ERROR]There was an unknown error" << std::endl;
            break;
    }


}

db::~db()
{
    std::string query = "VACUUM INTO '" + m_dbName + ".bsql'";
    sqlite3_exec(m_db, query.c_str(), callback, nullptr, &m_err);
    sqlite3_close(m_db);
}

json db::query(const std::string& t_query)
{
    json queryResponse;
    tempQueryResponse.clear(); //clear any previous data
    counter = -1;
    m_rc = sqlite3_exec(m_db, t_query.c_str(), callback, nullptr, &m_err); //execute the query using sqlite engine
    if(m_rc != SQLITE_OK)
    {
        //there was an error in the query
        queryResponse[0]["Success"] = false;
        queryResponse[0]["Error"] = m_err;
    }
    else
    {
        //successful
        queryResponse[0]["Success"] = true;
        queryResponse[0]["Error"] = "";
        queryResponse.insert(queryResponse.begin() + 1, tempQueryResponse.begin(), tempQueryResponse.end());
    }
    return queryResponse;
}

int db::initializeDB()
{
    //Function to initialize the database
    //Return codes:
    //1 -> there was a problem reading from the persistent db
    //0 -> everything was okay
    //-1 -> persistent db does not exist, creating only an in-memory db
    sqlite3* persistentDB;
    std::string persistentDBName = m_dbName + ".bsql";
    if(std::filesystem::exists(persistentDBName))
    {
        m_rc = sqlite3_open(persistentDBName.c_str(), &persistentDB);
        //std::cout << "Failed to open the previously saved instance of this database!" << std::endl;
        if (m_rc) return 1; //if there was an error print it and return 1

        //start loading from saved instance into memory
        sqlite3_backup *loader = sqlite3_backup_init(m_db, "main", persistentDB, "main");
        if (loader)
        {
            (void) sqlite3_backup_step(loader, -1);
            (void) sqlite3_backup_finish(loader);
            sqlite3_close(persistentDB);
            std::filesystem::remove(persistentDBName); //loading was complete, hence remove it from disk
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return -1;
    }

}
