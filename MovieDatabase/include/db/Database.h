#pragma once
#include <sqlite_modern_cpp.h>
#include <string>

class Database
{
public:
    explicit Database(const std::string& path)
        : db(path) {}

    sqlite::database& get()
    {
        return db;
    }

private:
    sqlite::database db;
};