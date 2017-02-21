enable_testing()

add_subdirectory(lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRCS
        src/property_tests.cpp
        src/settings_holder_tests.cpp
        src/topic_tests.cpp
        src/dummy_node.cpp
        include/dummy_node.h
        src/node_tests.cpp
        src/linear_launcher_tests.cpp
        src/queue_adapter_factory_tests.cpp
        src/stl_queue_adapter_tests.cpp
        src/exec_tests.cpp
        src/concurrent_queue_adapter_tests.cpp
        src/task_packer_tests.cpp
        src/service_tests.cpp
        include/flag_setter.h src/flag_setter.cpp)


add_executable(tests ${SRCS})
target_link_libraries(tests gtest gtest_main gmock rrc)
target_include_directories(tests PUBLIC include/)
add_test(tests tests)

