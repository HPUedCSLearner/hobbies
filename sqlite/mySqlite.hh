#ifndef __MY_SQLITE__
#define __MY_SQLITE__

#include "Noncopyable.hh"

#include <stdio.h>
#include <string>
#include <sqlite3.h>

using std::string;

class MySqlite : Noncopyable {
public:
    MySqlite(const string name)
    :dbName(name)
    {
        int rc = sqlite3_open(dbName.c_str(), &db);
        if (rc) {
            fprintf(stderr, "Can't open dataBase %s, err:%s\n", dbName.c_str(), sqlite3_errmsg(db));
        } else {
            fprintf(stderr, "open dataBase %s Successful,\n", dbName.c_str());
        }
    }
    ~MySqlite() { sqlite3_close(db); }

private:
    string dbName;
    sqlite3 * db;
};

#endif