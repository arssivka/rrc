cmake_minimum_required(VERSION 3.0)
project(rrc VERSION 0.0.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -Wall")

option(USE_TCMALLOC "Use full version of tcmalloc library" ON)
option(BUILD_TEST "Build tests." ON)

add_subdirectory(lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SRCS
        include/rrc/core/abstract_launcher.h
        include/rrc/core/node.h
        include/rrc/core/non_copyable.h
        src/rrc/core/property.cpp
        include/rrc/core/property.h
        include/rrc/core/copy_on_write.h
        src/rrc/core/abstract_task_queue_adapter.cpp
        include/rrc/core/abstract_task_queue_adapter.h
        include/rrc/core/topic_holder.h
        src/rrc/core/topic.cpp
        include/rrc/core/topic.h
        src/rrc/core/linear_launcher.cpp
        include/rrc/core/linear_launcher.h
        include/rrc/core/task_packer.h
        include/rrc/core/abstract_queue_adapter.h
        include/rrc/core/concurrent_queue_adapter.h
        include/rrc/core/stl_queue_adapter.h
        src/rrc/core/mechanisms_holder.cpp
        include/rrc/core/mechanisms_holder.h
        src/rrc/core/rate.cpp
        include/rrc/core/rate.h
        src/rrc/core/advertising_mechanism.cpp
        include/rrc/core/advertising_mechanism.h
        src/rrc/core/system_mechanism.cpp
        include/rrc/core/system_mechanism.h
        src/rrc/core/node.cpp
        include/rrc/core/queue_adapter_factory.h
        src/rrc/core/service.cpp
        include/rrc/core/service.h
        include/rrc/core/service_holder.h
        src/rrc/core/service_mechanism.cpp
        include/rrc/core/service_mechanism.h
        include/rrc/core/settings_holder.h
        src/rrc/core/settings_mechanism.cpp
        include/rrc/core/settings_mechanism.h include/rrc/core/defines.h)

configure_file("${PROJECT_SOURCE_DIR}/template/VersionDefines.h.in"
        "${PROJECT_BINARY_DIR}/VersionDefines.h")


add_library(rrc ${SRCS})
target_link_libraries(rrc variant concurrentqueue)
target_include_directories(rrc PUBLIC include)

if(BUILD_TEST)
    add_subdirectory(test)
endif()