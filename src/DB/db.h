//
// Created by sinister on 11/16/22.
//

#ifndef BONKSQL_DB_H
#define BONKSQL_DB_H

#include <string>
#include <iostream>
#include "sqlite/sqlite3.h"

class db
{
public:
    db();
    ~db();
    void query(const std::string& t_query);
private:
    sqlite3* m_db{};
    char* m_err = nullptr;
    int m_rc;
};

#endif //BONKSQL_DB_H
