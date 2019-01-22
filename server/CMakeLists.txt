cmake_minimum_required( VERSION 3.11 )
project( server C )

set( CMAKE_C_STANDARD 11 )

add_executable( server )

target_sources( server
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/source/main.c" )

target_include_directories( server INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/source" )