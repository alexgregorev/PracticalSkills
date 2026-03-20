#include "db/MovieRepository.h"

std::vector<std::string> get_directors(sqlite3_int64 id, sqlite::database& db)
{
    std::vector<std::string> res;
    db << "select p.name from directors d join persons p on d.personid=p.rowid where d.movieid=?;"
       << id
       >> [&](std::string const& name){ res.push_back(name); };
    return res;
}

std::vector<std::string> get_writers(sqlite3_int64 id, sqlite::database& db)
{
    std::vector<std::string> res;
    db << "select p.name from writers w join persons p on w.personid=p.rowid where w.movieid=?;"
       << id
       >> [&](std::string const& name){ res.push_back(name); };
    return res;
}

std::vector<casting_role> get_cast(sqlite3_int64 id, sqlite::database& db)
{
    std::vector<casting_role> res;
    db << "select p.name, c.role from casting c join persons p on c.personid=p.rowid where c.movieid=?;"
       << id
       >> [&](std::string const& name, std::string const& role){ res.push_back({name, role}); };
    return res;
}

movie_list get_movies(sqlite::database& db)
{
    movie_list movies;

    db << "select rowid,* from movies;"
       >> [&](sqlite3_int64 id, std::string title, int year, int length)
       {
           movies.push_back(movie{
               (unsigned)id,
               title,
               year,
               (unsigned)length,
               get_cast(id, db),
               get_directors(id, db),
               get_writers(id, db)
           });
       };

    return movies;
}
