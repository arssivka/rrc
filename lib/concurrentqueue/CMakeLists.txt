cmake_minimum_required(VERSION 3.0)
project(concurrentqueue CXX)

set(SRCS include/concurrentqueue.h
         include/blockingconcurrentqueue.h)

add_library(concurrentqueue INTERFACE)
target_include_directories(concurrentqueue INTERFACE include)
target_sources(concurrentqueue INTERFACE ${SRSC})