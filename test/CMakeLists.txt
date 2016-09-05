enable_testing()

add_subdirectory(lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRCS
        src/PropertyTests.cpp
        src/SettingsTests.cpp
        src/TSLookUpTests.cpp
        src/MessageTests.cpp
        src/MetaTableTests.cpp
        src/TopicTest.cpp
        src/MessageListenerTests.cpp
        src/TaskQueueTests.cpp
        src/RootNodeTest.cpp
        src/DummyNode.cpp
        include/DummyNode.h
        src/BillboardTests.cpp
        src/RecieveGuardTests.cpp
        src/NodeTest.cpp
        src/SubscriberTest.cpp
        src/LinearLauncherTest.cpp
        src/AdvertiserTests.cpp
        src/SendGuardTests.cpp)

set(PROTOS
        proto/Message.proto)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOS})


add_executable(tests ${SRCS} ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(tests gtest gtest_main rrc ${PROTOBUF_LIBRARIES})
target_include_directories(tests PUBLIC ${PROTOBUF_INCLUDE_DRIS})

