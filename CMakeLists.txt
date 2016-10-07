cmake_minimum_required(VERSION 3.0)
project(rrc VERSION 0.0.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -Wall")

option(USE_TCMALLOC "Use full version of tcmalloc library" ON)
option(BUILD_TEST "Build tests." ON)

find_package(Protobuf REQUIRED)
find_package(TCMalloc REQUIRED)

add_subdirectory(lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SRCS
        include/rrc/core/AbstractLauncher.h
        include/rrc/core/AbstractNode.h
        src/rrc/core/SettingsHolder.cpp
        include/rrc/core/SettingsHolder.h
        include/rrc/core/Advertiser.h
        include/rrc/core/Subscriber.h
        include/rrc/core/Message.h
        include/rrc/core/NonCopyable.h
        include/rrc/core/QueueMessageListener.h
        src/rrc/core/Property.cpp
        include/rrc/core/Property.h
        include/rrc/core/CopyOnWrite.h
        src/rrc/core/TaskQueue.cpp
        include/rrc/core/TaskQueue.h
        src/rrc/core/QueueMessageListener.cpp
        include/rrc/core/Billboard.h
        src/rrc/core/Topic.cpp include/rrc/core/Topic.h
        src/rrc/core/MetaTable.cpp
        include/rrc/core/MetaTable.h
        src/rrc/core/RootNode.cpp
        include/rrc/core/RootNode.h
        src/rrc/core/Node.cpp
        include/rrc/core/Node.h
        src/rrc/core/LinearLauncher.cpp
        include/rrc/core/LinearLauncher.h
        src/rrc/core/UnregisteredTypeException.cpp
        include/rrc/core/UnregisteredTypeException.h
        include/rrc/core/SendGuard.h
        include/rrc/core/ReceiveGuard.h
        src/rrc/core/IncompatibleTypesException.cpp
        include/rrc/core/IncompatibleTypesException.h
        include/rrc/core.h
        include/rrc/core/MessageFactory.h
        include/rrc/core/AbstractMessageFactory.h
        include/rrc/core/AbstractMessageListener.h
        src/rrc/core/AbstractMessageListener.cpp
        include/rrc/core/LimitedSizeMessageListener.h
        include/rrc/core/AbstractPropertyListener.h
        include/rrc/core/PropertyListener.h
        src/rrc/core/PropertyListener.cpp
        include/rrc/core/AbstractMessageFilter.h
        src/rrc/core/BypassMessageFilter.cpp
        include/rrc/core/BypassMessageFilter.h
        src/rrc/core/RejectMessageFilter.cpp
        include/rrc/core/RejectMessageFilter.h
        src/rrc/core/TypeIdMessageFilter.cpp
        include/rrc/core/TypeIdMessageFilter.h
        src/rrc/core/CallbackMessageFilter.cpp
        include/rrc/core/CallbackMessageFilter.h
        src/rrc/core/PropertyDictionary.cpp
        include/rrc/core/PropertyDictionary.h)

configure_file("${PROJECT_SOURCE_DIR}/template/VersionDefines.h.in"
               "${PROJECT_BINARY_DIR}/VersionDefines.h")



add_library(rrc ${SRCS} ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(rrc ${PROTOBUF_LIBRARIES} ${TCMalloc_LIBRARIES} variant concurrentqueue)
target_include_directories(rrc PUBLIC include ${PROTOBUF_INCLUDE_DIRS} ${TCMalloc_INCLUDE_DIRS})

if(BUILD_TEST)
    add_subdirectory(test)
endif()