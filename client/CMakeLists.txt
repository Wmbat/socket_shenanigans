cmake_minimum_required( VERSION 3.11 )
project( client C )

set( CMAKE_C_STANDARD 11 )

add_executable( client )

target_sources( client
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/source/main.c" )

target_include_directories( client INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/source" )