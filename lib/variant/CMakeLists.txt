cmake_minimum_required(VERSION 3.0)
project(variant CXX)

set(SRCS include/mapbox/optional.hpp
         include/mapbox/recursive_wrapper.hpp
         include/mapbox/variant.hpp
         include/mapbox/variant_io.hpp)

add_library(variant INTERFACE)
target_include_directories(variant INTERFACE include)
target_sources(variant INTERFACE ${SRSC})