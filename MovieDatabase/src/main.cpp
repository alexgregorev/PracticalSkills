#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <sqlite_modern_cpp.h>

// ===== utils =====
std::vector<char> load_file(const std::string& path)
{
    std::vector<char> data;

    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) return data;

    auto size = file.tellg();
    file.seekg(0);

    data.resize(size);
    file.read(data.data(), size);

    return data;
}

// ===== main =====
int main()
{
    try
    {
        std::filesystem::create_directories("data");
        std::filesystem::remove("data/test.db");
        sqlite::database db("data/test.db");

        std::cout << "DB: " << std::filesystem::absolute("data/test.db") << "\n";
        std::cout << "Removing: "
                  << std::filesystem::absolute("data/test.db") << "\n";

        // ===== TABLES =====
        db << R"(
            CREATE TABLE IF NOT EXISTS movies (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                title TEXT,
                year INTEGER,
                length INTEGER
            );
        )";

        db << R"(
            CREATE TABLE IF NOT EXISTS media (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                movieid INTEGER,
                name TEXT,
                text TEXT,
                blob BLOB
            );
        )";

        db << R"(
            CREATE TABLE IF NOT EXISTS persons (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT
            );
        )";

        db << R"(
            CREATE TABLE IF NOT EXISTS casting (
                movieid INTEGER,
                personid INTEGER,
                role TEXT
            );
        )";

        // ===== CLEAN (чтобы не дублировалось при каждом запуске) =====
        db << "DELETE FROM casting;";
        db << "DELETE FROM persons;";
        db << "DELETE FROM media;";
        db << "DELETE FROM movies;";

        // ===== INSERT MOVIE =====
        db << "INSERT INTO movies (title, year, length) VALUES (?, ?, ?);"
           << "Inception" << 2010 << 148;

        // ===== INSERT PERSONS =====
        db << "INSERT INTO persons (name) VALUES (?);" << "Leonardo DiCaprio";
        db << "INSERT INTO persons (name) VALUES (?);" << "Joseph Gordon-Levitt";

        // ===== CASTING =====
        db << "INSERT INTO casting (movieid, personid, role) VALUES (?, ?, ?);"
           << 1 << 1 << "Cobb";

        db << "INSERT INTO casting (movieid, personid, role) VALUES (?, ?, ?);"
           << 1 << 2 << "Arthur";

        // ===== MEDIA =====
        std::vector<char> fake_blob = {'J','P','G'};

        db << "INSERT INTO media (movieid, name, text, blob) VALUES (?, ?, ?, ?);"
           << 1
           << "poster.jpg"
           << "Main poster"
           << fake_blob;

        // ===== PRINT MOVIES =====
        std::cout << "\n--- Movies ---\n";

        db << "SELECT id, title, year, length FROM movies;"
           >> [](int id, std::string title, int year, int length)
           {
               std::cout << id << " | " << title
                         << " (" << year << ") "
                         << length << " min\n";
           };

        // ===== PRINT CASTING (JOIN) =====
        std::cout << "\n--- Casting ---\n";

        db << R"(
            SELECT m.title, p.name, c.role
            FROM casting c
            JOIN movies m ON m.id = c.movieid
            JOIN persons p ON p.id = c.personid;
        )"
        >> [](std::string title, std::string actor, std::string role)
        {
            std::cout << title << " | "
                      << actor << " as "
                      << role << "\n";
        };

        // ===== PRINT MEDIA =====
        std::cout << "\n--- Media ---\n";

        db << "SELECT id, movieid, name, text, blob FROM media;"
           >> [](int id, int movieid, std::string name, std::string text, std::vector<char> blob)
           {
               std::cout << id << " | movie=" << movieid
                         << " | " << name
                         << " | " << text
                         << " | size=" << blob.size() << "\n";
           };

        // ===== CASTING BY MOVIE =====
        std::cout << "\n--- Casting for movie 1 ---\n";

        db << R"(
            SELECT p.name, c.role
            FROM casting c
            JOIN persons p ON p.id = c.personid
            WHERE c.movieid = ?;
        )"
        << 1
        >> [](std::string actor, std::string role)
        {
            std::cout << actor << " -> " << role << "\n";
        };
    }
    catch (std::exception const& e)
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }

    return 0;
}