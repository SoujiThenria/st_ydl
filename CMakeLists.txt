cmake_minimum_required(VERSION 3.10)

# Set version
set(RELEASE_SERVICE_VERSION_MAJOR "2")
set(RELEASE_SERVICE_VERSION_MINOR "3")
set(RELEASE_SERVICE_VERSION_MICRO "1")
set(RELEASE_SERVICE_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}.${RELEASE_SERVICE_VERSION_MICRO}")

# set the project name
project(st_ydl VERSION ${RELEASE_SERVICE_VERSION})

set(CMAKE_CXX_STANDARD 17)

# Enable when compiling for Windows
if (WIN32)
    set(Boost_ARCHITECTURE "-x64")
endif (WIN32)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.75.0 COMPONENTS thread chrono)

# add version file
configure_file(src/st_ydl_version.h.in st_ydl_version.h)


add_subdirectory(src)
