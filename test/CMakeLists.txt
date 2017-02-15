enable_testing()

add_subdirectory(lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRCS
        src/core/PropertyTests.cpp
        src/core/SettingsHolderTests.cpp
        src/core/TopicTest.cpp
        src/core/DummyNode.cpp
        include/DummyNode.h
        include/QueueAdapter.h
        src/core/NodeTest.cpp
        src/core/LinearLauncherTest.cpp
        src/core/QueueAdapterFactoryTests.cpp
        src/core/BufferTests.cpp
        src/core/STLQueueAdapterTests.cpp
        src/core/TaskQueueAdapterTests.cpp
        src/core/ConcurrentQueueAdapterTests.cpp
        src/core/TaskHubTests.cpp
        src/core/ServiceTests.cpp
        src/core/BooleanTests.cpp
        src/core/StringTests.cpp)


add_executable(tests ${SRCS})
target_link_libraries(tests gtest gtest_main gmock rrc)
add_test(tests tests)

