cmake_minimum_required( VERSION 3.11 )

project( socket_shenanigans C )

set( CMAKE_C_STANDARD 11 )

add_executable( socket_shenanigans )

target_sources( socket_shenanigans
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/main.c" )



