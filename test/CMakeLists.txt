enable_testing()

add_subdirectory(lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRCS
        src/core/property_tests.cpp
        src/core/settings_holder_tests.cpp
        src/core/topic_tests.cpp
        src/core/dummy_node.cpp
        include/dummy_node.h
        src/core/node_tests.cpp
        src/core/linear_launcher_test.cpp
        src/core/queue_adapter_factory_tests.cpp
        src/core/stl_queue_adapter_tests.cpp
        src/core/exec_tests.cpp
        src/core/concurrent_queue_adapter_tests.cpp
        src/core/task_packer_tests.cpp
        src/core/service_tests.cpp
        )


add_executable(tests ${SRCS})
target_link_libraries(tests gtest gtest_main gmock rrc)
add_test(tests tests)

