enable_testing()

add_subdirectory(lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRCS
        src/core/PropertyTests.cpp
        src/core/SettingsHolderTests.cpp
        src/core/TopicTest.cpp
        src/core/QueueMessageListenerTests.cpp
        src/core/TaskQueueTests.cpp
        src/core/RootNodeTest.cpp
        src/core/DummyNode.cpp
        include/DummyNode.h
        src/core/BillboardTests.cpp
        src/core/NodeTest.cpp
        src/core/QueueSubscriberTest.cpp
        src/core/LinearLauncherTest.cpp
        src/core/AdvertiserTests.cpp
        src/core/LimitedSizeSubscriberTests.cpp
        src/core/TypeIdMessageFilterTests.cpp
        src/core/RejectMessageFilterTest.cpp
        src/core/BypassMessageFilterTests.cpp
        src/core/CallbackMessageFilterTest.cpp
        src/core/MetaTests.cpp
        src/core/MetaArrayTests.cpp
        src/core/MessageTests.cpp
        src/core/VarintTests.cpp
        src/core/MetaVarintTests.cpp
        src/core/StructureTypeQuantityGeneratorTests.cpp
        src/core/VarintEncodeSequenceTests.cpp
        src/core/ArrayRefernceTets.cpp src/core/TypeIdentifiersArrayTests.cpp)


add_executable(tests ${SRCS})
target_link_libraries(tests gtest gtest_main gmock rrc)
add_test(tests tests)

