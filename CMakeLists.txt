cmake_minimum_required(VERSION 3.0)
project(rrc VERSION 0.0.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -Wall")

option(USE_TCMALLOC "Use full version of tcmalloc library" ON)
option(BUILD_TEST "Build tests." OFF)

find_package(Protobuf REQUIRED)
find_package(TCMalloc REQUIRED)

add_subdirectory(lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SRCS
        src/rrc/Core.cpp
        include/rrc/Core.h
        include/rrc/Clock.h
        src/rrc/ID.cpp
        include/rrc/ID.h
        src/rrc/Node.cpp
        include/rrc/Node.h
        src/rrc/Settings.cpp
        include/rrc/Settings.h
        include/rrc/Advertiser.h
        include/rrc/Subscriber.h
        include/rrc/Message.h
        include/rrc/Pipe.h
        include/rrc/NonCopyable.h
        include/rrc/TopicConnector.h
        include/rrc/MessageListener.h
        include/rrc/TSPriorityQueue.h
        include/rrc/TSQueue.h
        src/rrc/Property.cpp
        include/rrc/Property.h
        include/rrc/TSLookUp.h
        include/rrc/CopyOnWrite.h
        src/rrc/MessageSender.cpp
        include/rrc/MessageSender.h
        include/rrc/TSList.h
        src/rrc/TaskQueue.cpp
        include/rrc/TaskQueue.h
        src/rrc/TopicConnector.cpp
        include/rrc/AtomicWithNotifications.h src/rrc/MessageListener.cpp)

configure_file("${PROJECT_SOURCE_DIR}/template/VersionDefines.h.in"
        "${PROJECT_BINARY_DIR}/VersionDefines.h")

add_library(rrc ${SRCS})
target_link_libraries(rrc ${PROTOBUF_LIBRARIES} ${TCMalloc_LIBRARIES} variant)
target_include_directories(rrc PUBLIC include ${PROTOBUF_INCLUDE_DIRS} ${TCMalloc_INCLUDE_DIRS})

if(BUILD_TEST)
    add_subdirectory(test)
endif()