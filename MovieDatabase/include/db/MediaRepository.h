#pragma once
#include "models/Media.h"
#include <sqlite_modern_cpp.h>

bool add_media(sqlite_int64 movieid, std::string_view name, std::string_view desc, std::vector<char> content, sqlite::database& db);
media_list get_media(sqlite_int64 movieid, sqlite::database& db);
bool delete_media(sqlite_int64 mediaid, sqlite::database& db);
