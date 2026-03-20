#pragma once
#include "models/Movie.h"
#include <sqlite_modern_cpp.h>

movie_list get_movies(sqlite::database& db);