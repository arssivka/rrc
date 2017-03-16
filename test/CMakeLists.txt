enable_testing()

add_subdirectory(lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRCS
        tst/topic_tests.cpp
        src/dummy_node.cpp
        include/dummy_node.h
        tst/node_tests.cpp
        tst/linear_launcher_tests.cpp
        tst/concurrent_task_queue_tests.cpp
        tst/service_holder_tests.cpp
        include/flag_setter.h
        src/flag_setter.cpp
        tst/topic_holder_tests.cpp
        tst/lockfree_launcher_tests.cpp
        tst/buffer_tests.cpp)


add_executable(tests ${SRCS})
target_link_libraries(tests gtest gtest_main gmock rrc)
target_include_directories(tests PUBLIC include/)
add_test(tests tests)

