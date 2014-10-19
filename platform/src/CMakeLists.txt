cmake_minimum_required (VERSION 2.8.11)

set(CMAKE_C_FLAGS "-g -Wall -std=c99")
project (fcs-platform)

# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
add_subdirectory (chr-um6)
add_subdirectory (maestro)
add_subdirectory (platform)