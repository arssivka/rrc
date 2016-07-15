cmake_minimum_required(VERSION 3.0)
project(core)

find_package(Protobuf REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SRCS src/Core.cpp include/Core.h src/Core.cpp include/Core.h src/ID.cpp include/ID.h src/Node.cpp
        include/Node.h src/Settings.cpp include/Settings.h src/Scheduler.cpp include/Scheduler.h
        include/Advertiser.h include/Subscriber.h include/Message.h include/MessageFactory.h include/Pool.h
        include/Client.h include/Service.h include/Pipe.h include/Responce.h include/NonCopyable.h include/Topic.h include/TopicListener.h)

configure_file("${PROJECT_SOURCE_DIR}/template/VersionDefines.h.in"
               "${PROJECT_BINARY_DIR}/VersionDefines.h")

add_library(rrc ${SRCS})
target_link_libraries(rrc ${PROTOBUF_LIBRARIES})
target_include_directories(rrc PUBLIC include ${PROTOBUF_INCLUDE_DIRS})