cmake_minimum_required(VERSION 3.0)
project(rrc VERSION 0.0.0.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -Wall")

option(USE_TCMALLOC "Use full version of tcmalloc library" ON)

find_package(Protobuf REQUIRED)
find_package(TCMalloc REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SRCS
        src/rrc/Core.cpp
        include/rrc/Core.h
        src/rrc/Core.cpp
        include/rrc/Core.h
        src/rrc/ID.cpp
        include/rrc/ID.h
        src/rrc/Node.cpp
        include/rrc/Node.h
        src/rrc/Settings.cpp
        include/rrc/Settings.h
        src/rrc/Scheduler.cpp
        include/rrc/Scheduler.h
        include/rrc/Advertiser.h
        include/rrc/Subscriber.h
        include/rrc/Message.h
        include/rrc/MessageFactory.h
        include/rrc/Pool.h
        include/rrc/Client.h
        include/rrc/Service.h
        include/rrc/Pipe.h
        include/rrc/Response.h
        include/rrc/NonCopyable.h
        include/rrc/Topic.h
        include/rrc/TopicListener.h
        include/rrc/TSPriorityQueue.h
        include/rrc/TSQueue.h
        src/rrc/SettingsField.cpp
        include/rrc/SettingsField.h
        include/rrc/TSLookUp.h
)

configure_file("${PROJECT_SOURCE_DIR}/template/VersionDefines.h.in"
        "${PROJECT_BINARY_DIR}/VersionDefines.h")

add_library(rrc ${SRCS})
target_link_libraries(rrc ${PROTOBUF_LIBRARIES} ${TCMalloc_LIBRARIES})
target_include_directories(rrc PUBLIC include ${PROTOBUF_INCLUDE_DIRS} ${TCMalloc_INCLUDE_DIRS})