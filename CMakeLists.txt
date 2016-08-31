cmake_minimum_required(VERSION 3.0)
project(rrc VERSION 0.0.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -Wall")

option(USE_TCMALLOC "Use full version of tcmalloc library" ON)
option(BUILD_TEST "Build tests." ON)

find_package(Protobuf REQUIRED)
find_package(TCMalloc REQUIRED)

add_subdirectory(lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SRCS
        include/rrc/LauncherBase.h
        include/rrc/NodeBase.h
        src/rrc/Settings.cpp
        include/rrc/Settings.h
        include/rrc/Advertiser.h
        include/rrc/Subscriber.h
        include/rrc/Message.h
        include/rrc/NonCopyable.h
        include/rrc/MessageListener.h
        src/rrc/Property.cpp
        include/rrc/Property.h
        include/rrc/TSLookUp.h
        include/rrc/CopyOnWrite.h
        src/rrc/MessageSender.cpp
        include/rrc/MessageSender.h
        src/rrc/TaskQueue.cpp
        include/rrc/TaskQueue.h
        src/rrc/MessageListener.cpp
        include/rrc/Billboard.h
        src/rrc/Topic.cpp include/rrc/Topic.h
        src/rrc/MetaTable.cpp
        include/rrc/MetaTable.h
        src/rrc/RootNode.cpp
        include/rrc/RootNode.h
        src/rrc/Node.cpp
        include/rrc/Node.h
        src/rrc/LinearLauncher.cpp
        include/rrc/LinearLauncher.h
        src/rrc/UnregisteredTypeException.cpp
        include/rrc/UnregisteredTypeException.h
        include/rrc/SendGuard.h
        include/rrc/ReceiveGuard.h
        src/rrc/IncompatibleTypesException.cpp
        include/rrc/IncompatibleTypesException.h)

configure_file("${PROJECT_SOURCE_DIR}/template/VersionDefines.h.in"
        "${PROJECT_BINARY_DIR}/VersionDefines.h")

add_library(rrc ${SRCS})
target_link_libraries(rrc ${PROTOBUF_LIBRARIES} ${TCMalloc_LIBRARIES} variant concurrentqueue)
target_include_directories(rrc PUBLIC include ${PROTOBUF_INCLUDE_DIRS} ${TCMalloc_INCLUDE_DIRS})

if(BUILD_TEST)
    add_subdirectory(test)
endif()