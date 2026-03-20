cmake_minimum_required(VERSION 3.16)
project(MovieDatabase)

set(CMAKE_CXX_STANDARD 17)

# =========================
# Network settings (optional)
# =========================
set(CMAKE_TLS_VERIFY OFF)
set(FETCHCONTENT_QUIET OFF)

include(FetchContent)

# =========================
# Options
# =========================
option(OFFLINE_MODE "Use local dependencies only" OFF)

# =========================
# SQLite
# =========================
if(OFFLINE_MODE AND EXISTS "${CMAKE_SOURCE_DIR}/external/sqlite/sqlite3.c")

    message(STATUS "Using LOCAL SQLite")
    set(SQLITE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/sqlite")

else()

    message(STATUS "Fetching SQLite from internet")

    FetchContent_Declare(
        sqlite
        URL https://www.sqlite.org/2024/sqlite-amalgamation-3450200.zip
    )

    FetchContent_MakeAvailable(sqlite)

    set(SQLITE_SOURCE_DIR ${sqlite_SOURCE_DIR})

endif()

# =========================
# sqlite_modern_cpp (HEADER ONLY)
# =========================

set(SQLITE_MODERN_CPP_DIR "${CMAKE_SOURCE_DIR}/external/sqlite_modern_cpp/hdr")

# =========================
# SQLite library
# =========================
add_library(sqlite3 STATIC
    ${SQLITE_SOURCE_DIR}/sqlite3.c
)

target_include_directories(sqlite3 PUBLIC
    ${SQLITE_SOURCE_DIR}
)

# Optional (recommended for Windows)
target_compile_definitions(sqlite3 PRIVATE
    SQLITE_THREADSAFE=1
    _CRT_SECURE_NO_WARNINGS
)

# =========================
# Executable
# =========================
add_executable(MovieDatabase
    src/main.cpp
    src/utils/StringUtils.cpp
    src/utils/FileUtils.cpp
    src/db/MovieRepository.cpp
    src/db/MediaRepository.cpp
)

target_include_directories(MovieDatabase PUBLIC
    ${SQLITE_SOURCE_DIR}
    ${SQLITE_MODERN_CPP_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(MovieDatabase PRIVATE sqlite3)