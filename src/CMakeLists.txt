cmake_minimum_required(VERSION 3.10)

# set the project name
project(st_ydl)

# add the executable
add_executable(st_ydl main.cpp config.cpp)

install(
    TARGETS st_ydl
    DESTINATION "/usr/local/bin/"
)