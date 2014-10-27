project(Gps)

add_library (gps gps.c gps.h)

target_include_directories (gps PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})