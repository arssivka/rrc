enable_testing()

add_subdirectory(lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRCS
        src/core/PropertyTests.cpp
        src/core/SettingsHolderTests.cpp
        src/core/TopicTest.cpp
        src/core/TaskQueueTests.cpp
        src/core/DummyNode.cpp
        include/DummyNode.h
        src/core/BillboardTests.cpp
        src/core/NodeTest.cpp
        src/core/LinearLauncherTest.cpp
        src/core/AdvertiserTests.cpp
        src/core/QueueAdapterFactoryTests.cpp
        src/core/BufferTests.cpp)


add_executable(tests ${SRCS})
target_link_libraries(tests gtest gtest_main gmock rrc)
add_test(tests tests)

