
set(CMAKE_C_FLAGS "-g -Wall -Werror")
add_executable (fcs-platform main.c chr_sensor.c platform.c servo_controller.c)

include_directories(${Maestro_SOURCE_DIR})
include_directories(${Gps_SOURCE_DIR})
include_directories(${CHR-UM6_SOURCE_DIR})
target_link_libraries (fcs-platform LINK_PUBLIC gps um6_wire_format posix_sys chr_um6 m)