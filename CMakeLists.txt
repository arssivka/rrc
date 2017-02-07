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
        include/rrc/core/MessageListener.h
        src/rrc/core/MessageListener.cpp
        include/rrc/core/AbstractPropertyListener.h
        include/rrc/core/PropertyListener.h
        src/rrc/core/PropertyListener.cpp
        src/rrc/core/PropertyDictionary.cpp
        include/rrc/core/PropertyDictionary.h
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
        include/rrc/core/Serializer.h
        include/rrc/core/Buffer.h
        include/rrc/core/StructureTypeQuantityGenerator.h
        src/rrc/core/Buffer.cpp
        include/rrc/core/QueueAdapterFactory.h
        include/rrc/core/TaskCapture.h)

configure_file("${PROJECT_SOURCE_DIR}/template/VersionDefines.h.in"
        "${PROJECT_BINARY_DIR}/VersionDefines.h")


add_library(rrc ${SRCS})
target_link_libraries(rrc variant concurrentqueue)
target_include_directories(rrc PUBLIC include)

if(BUILD_TEST)
    add_subdirectory(test)
endif()