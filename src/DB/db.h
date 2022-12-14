//
// Created by sinister on 11/16/22.
//

#ifndef BONKSQL_DB_H
#define BONKSQL_DB_H

#include <string>
#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"
#include "nlohmann/json.hpp"
#include <filesystem>

using json = nlohmann::json;

class db
{
public:
    explicit db(const std::string& t_dbName);
    ~db();
    json query(const std::string& t_query);
private:
    sqlite3* m_db{};
    std::string m_dbName;
    char* m_err = nullptr;
    int m_rc;

    //private functions
    int initializeDB();
};

#endif //BONKSQL_DB_H
