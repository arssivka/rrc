cmake_minimum_required(VERSION 3.0)
project(rrc VERSION 0.0.0.0)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -Wall")

add_subdirectory(core)