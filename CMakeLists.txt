cmake_minimum_required(VERSION 3.0)
include(FindPkgConfig)
pkg_check_modules(CURLPP REQUIRED curlpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CURL_MIN_VERSION "7.28.0")
 
project(lolPoller)
 
include_directories(include)

link_directories(/usr/local/lib)

file(GLOB SOURCES "src/*.cpp")
 
add_executable(lolPoller ${SOURCES})
target_link_libraries(lolPoller curl curlpp)
