//
// Created by sinister on 11/16/22.
//

#include "db.h"

static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;

    for(i = 0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
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

void db::query(const std::string& t_query)
{
    m_rc = sqlite3_exec(m_db, t_query.c_str(), callback, nullptr, &m_err);
    if(m_rc != SQLITE_OK)
    {
        std::cout << "Error in SQL query: " << m_err << std::endl;
        //errors in the query
        //handle this
    }
}
