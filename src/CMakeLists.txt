cmake_minimum_required(VERSION 3.10)

# add the executable
add_executable(st_ydl
        main.cpp
        st_ydl.cpp
        ydl_data.cpp
        )

target_link_libraries(st_ydl PUBLIC
        ${Boost_LIBRARIES}
        )

# for the config file st_ydl_version.in.h
target_include_directories(st_ydl PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

install(
    TARGETS st_ydl
    DESTINATION "/usr/local/bin/"
)
