cmake_minimum_required (VERSION 2.8.11)

set(CMAKE_C_FLAGS "-g -Wall -std=c99 -Werror")
project (fcs-platform)

add_subdirectory ("../deps/chr-um6" "${CMAKE_CURRENT_BINARY_DIR}/chr-um6")
add_subdirectory (gps)
add_subdirectory (platform)