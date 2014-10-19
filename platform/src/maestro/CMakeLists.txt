project(Maestro)

add_library (maestro maestro.c maestro.h)

target_include_directories (maestro PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})