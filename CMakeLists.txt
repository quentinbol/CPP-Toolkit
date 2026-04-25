cmake_minimum_required(VERSION 3.16)

project(EventLoop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

option(BUILD_WATCHABLE "Build Watchable demo target" ON)
option(BUILD_SORTER "Build Sorter demo target" ON)
option(BUILD_EVENTLOOP "Build EventLoop demo target" ON)

if(BUILD_EVENTLOOP)
    add_subdirectory(EventLoop)
endif()

if(BUILD_WATCHABLE)
    add_subdirectory(Watchable)
endif()

if(BUILD_SORTER)
    add_subdirectory(Sorter)
endif()

if(NOT BUILD_WATCHABLE AND NOT BUILD_SORTER AND NOT BUILD_EVENTLOOP)
    message(WARNING "All build options are OFF. No targets will be built.")
endif()
