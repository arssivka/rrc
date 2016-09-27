enable_testing()

add_subdirectory(lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRCS
        src/core/PropertyTests.cpp
        src/core/SettingsTests.cpp
        src/core/MessageTests.cpp
        src/core/MetaTableTests.cpp
        src/core/TopicTest.cpp
        src/core/QueueMessageListenerTests.cpp
        src/core/TaskQueueTests.cpp
        src/core/RootNodeTest.cpp
        src/core/DummyNode.cpp
        include/DummyNode.h
        src/core/BillboardTests.cpp
        src/core/RecieveGuardTests.cpp
        src/core/NodeTest.cpp
        src/core/QueueSubscriberTest.cpp
        src/core/LinearLauncherTest.cpp
        src/core/AdvertiserTests.cpp
        src/core/SendGuardTests.cpp src/core/LimitedSizeSubscriberTests.cpp)

set(PROTOS
        proto/Message.proto)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOS})


add_executable(tests ${SRCS} ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(tests gtest gtest_main rrc ${PROTOBUF_LIBRARIES})
target_include_directories(tests PUBLIC ${PROTOBUF_INCLUDE_DRIS})

