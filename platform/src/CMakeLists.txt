cmake_minimum_required (VERSION 2.8.11)

set(CMAKE_C_FLAGS "-g -Wall -std=c99 -Werror")
project (fcs-platform)

add_subdirectory (chr-um6)
add_subdirectory (maestro)
add_subdirectory (gps)
add_subdirectory (platform)