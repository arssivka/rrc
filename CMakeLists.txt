cmake_minimum_required(VERSION 3.7)
project(serializer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(lib)
add_subdirectory(test)

find_package(Boost COMPONENTS program_options REQUIRED)
find_package(Threads)

set(SRC
        src/rrc/node.cpp
        include/rrc/node.h
        src/rrc/sender.cpp
        include/rrc/sender.h
        src/rrc/receiver.cpp
        include/rrc/receiver.h
        src/rrc/executor.cpp
        include/rrc/executor.h
        src/rrc/thread_group.cpp
        include/rrc/thread_group.h
        include/rrc/defines.h
        src/rrc/shared_library.cpp
        include/rrc/shared_library.h
        src/rrc/topic.cpp
        include/rrc/topic.h
        src/rrc/connector.cpp
        include/rrc/connector.h
        src/rrc/node_factory.cpp
        include/rrc/node_factory.h
        src/rrc/communication_connection.cpp
        include/rrc/communication_connection.h
        src/rrc/execution_connection.cpp
        include/rrc/execution_connection.h
        include/rrc/preferences.h)

add_library(rrc STATIC ${SRC})
target_include_directories(rrc PUBLIC
        include
        ${Boost_INCLUDE_DIRS})
target_link_libraries(rrc PUBLIC
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT})

if (UNIX)
    target_link_libraries(rrc PUBLIC dl)
endif (UNIX)

add_executable(rrc_exec src/rrc/main.cpp )
target_link_libraries(rrc_exec rrc)