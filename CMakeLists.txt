cmake_minimum_required(VERSION 3.0)
project(rrc VERSION 0.0.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -Wall")

option(USE_TCMALLOC "Use full version of tcmalloc library" ON)
option(BUILD_TEST "Build tests." ON)

add_subdirectory(lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SRCS
        include/rrc/core/AbstractLauncher.h
        include/rrc/core/Node.h
        include/rrc/core/NonCopyable.h
        src/rrc/core/Property.cpp
        include/rrc/core/Property.h
        include/rrc/core/CopyOnWrite.h
        src/rrc/core/AbstracrTaskQueueAdapter.cpp
        include/rrc/core/AbstracrTaskQueueAdapter.h
        include/rrc/core/TopicHolder.h
        src/rrc/core/Topic.cpp
        include/rrc/core/Topic.h
        src/rrc/core/LinearLauncher.cpp
        include/rrc/core/LinearLauncher.h
        include/rrc/core/TaskHub.h
        src/rrc/core/TaskHub.cpp
        include/rrc/core/AbstractQueueAdapter.h
        include/rrc/core/ConcurrentQueueAdapter.h
        include/rrc/core/STLQueueAdapter.h
        src/rrc/core/MechanismsHolder.cpp
        include/rrc/core/MechanismsHolder.h
        src/rrc/core/Rate.cpp
        include/rrc/core/Rate.h
        src/rrc/core/AdvertisingMechanism.cpp
        include/rrc/core/AdvertisingMechanism.h
        src/rrc/core/NodeMechanism.cpp
        include/rrc/core/NodeMechanism.h
        src/rrc/core/Node.cpp
        include/rrc/core/Buffer.h
        src/rrc/core/Buffer.cpp
        include/rrc/core/QueueAdapterFactory.h
        include/rrc/core/TaskCapture.h
        src/rrc/core/Service.cpp
        include/rrc/core/Service.h
        include/rrc/core/ServiceHolder.h
        src/rrc/core/ServiceMechanism.cpp
        include/rrc/core/ServiceMechanism.h)
        test/src/core/ServiceMechanism.cpp
        include/rrc/core/ServiceMechanism.h
        include/rrc/core/PropertyType.h
        src/rrc/core/Number.cpp
        include/rrc/core/Number.h
        include/rrc/core/Nil.h
        src/rrc/core/String.cpp
        include/rrc/core/String.h
        src/rrc/core/Boolean.cpp
        include/rrc/core/Boolean.h
        src/rrc/core/Array.cpp
        include/rrc/core/Array.h
        src/rrc/core/Table.cpp
        include/rrc/core/Table.h)

configure_file("${PROJECT_SOURCE_DIR}/template/VersionDefines.h.in"
        "${PROJECT_BINARY_DIR}/VersionDefines.h")


add_library(rrc ${SRCS})
target_link_libraries(rrc variant concurrentqueue)
target_include_directories(rrc PUBLIC include)

if(BUILD_TEST)
    add_subdirectory(test)
endif()