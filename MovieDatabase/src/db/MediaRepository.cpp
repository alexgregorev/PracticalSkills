#include "db/MediaRepository.h"

bool add_media(sqlite_int64 movieid, std::string_view name, std::string_view desc, std::vector<char> content, sqlite::database& db)
{
    try {
        // 🔥 FIX: явно указаны колонки (без id)
        db << "insert into media(movieid,name,text,blob) values(?,?,?,?)"
           << movieid << name.data() << desc.data() << content;

        return true;
    } catch (...) {
        return false;
    }
}

media_list get_media(sqlite_int64 movieid, sqlite::database& db)
{
    media_list list;

    db << "select rowid,* from media where movieid=?;"
       << movieid
       >> [&](sqlite3_int64 id, sqlite3_int64 mid, std::string name, std::optional<std::string> text, std::vector<char> blob)
       {
           list.push_back(media{(unsigned)id,(unsigned)mid,name,text,blob});
       };

    return list;
}

bool delete_media(sqlite_int64 mediaid, sqlite::database& db)
{
    try {
        db << "delete from media where rowid=?;" << mediaid;
        return true;
    } catch (...) {
        return false;
    }
}