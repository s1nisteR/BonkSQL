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

db::db()
{
    m_rc = sqlite3_open("test.db", &m_db);
    if(m_rc)
    {
        std::cout << "Could not open the database!" << std::endl;
    }
    else
    {
        std::cout << "Opened the database successfully!" << std::endl;
    }
}




db::~db()
{
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
