cmake_minimum_required(VERSION 3.23)
project(BonkSQL)

set(CMAKE_CXX_STANDARD 20)

include_directories(lib)

add_executable(BonkSQL src/main.cpp src/DB/db.cpp lib/sqlite/sqlite3.c)
