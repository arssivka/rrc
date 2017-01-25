cmake_minimum_required(VERSION 3.0)
project(rrc VERSION 0.0.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -Wall")

option(USE_TCMALLOC "Use full version of tcmalloc library" ON)
option(BUILD_TEST "Build tests." ON)

add_subdirectory(lib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SRCS
        include/rrc/core/AbstractLauncher.h
        include/rrc/core/AbstractNode.h
        src/rrc/core/SettingsHolder.cpp
        include/rrc/core/SettingsHolder.h
        include/rrc/core/Advertiser.h
        include/rrc/core/Subscriber.h
        include/rrc/core/NonCopyable.h
        src/rrc/core/Property.cpp
        include/rrc/core/Property.h
        include/rrc/core/CopyOnWrite.h
        src/rrc/core/TaskQueueWrapper.cpp
        include/rrc/core/TaskQueueWrapper.h
#        include/rrc/core/QueueMessageListener.h
#        src/rrc/core/QueueMessageListener.cpp
#        include/rrc/core/TopicHolder.h
#        src/rrc/core/Topic.cpp
#        include/rrc/core/Topic.h
        src/rrc/core/LinearLauncher.cpp
        include/rrc/core/LinearLauncher.h
#        include/rrc/core/AbstractMessageListener.h
#        src/rrc/core/AbstractMessageListener.cpp
        include/rrc/core/LimitedSizeMessageListener.h
        include/rrc/core/AbstractPropertyListener.h
        include/rrc/core/PropertyListener.h
        src/rrc/core/PropertyListener.cpp
#        include/rrc/core/AbstractMessageFilter.h
#        src/rrc/core/BypassMessageFilter.cpp
#        include/rrc/core/BypassMessageFilter.h
#        src/rrc/core/RejectMessageFilter.cpp
#        include/rrc/core/RejectMessageFilter.h
#        src/rrc/core/TypeIdMessageFilter.cpp
#        include/rrc/core/TypeIdMessageFilter.h
#        src/rrc/core/CallbackMessageFilter.cpp
#        include/rrc/core/CallbackMessageFilter.h
        src/rrc/core/PropertyDictionary.cpp
        include/rrc/core/PropertyDictionary.h
        include/rrc/core/AbstractQueueAdapter.h
        include/rrc/core/ConcurrentQueueAdapter.h
        include/rrc/core/STLQueueAdapter.h
        include/rrc/core/Mechanism.h
        include/rrc/core/RingQueueAdapter.h
        src/rrc/core/Engine.cpp
        include/rrc/core/Engine.h
        include/rrc/core/Pointer.h
        src/rrc/core/EngineWrapper.cpp
        include/rrc/core/EngineWrapper.h
        src/rrc/core/Rate.cpp
        include/rrc/core/Rate.h
#        src/rrc/core/AdvertisingMechanism.cpp
#        include/rrc/core/AdvertisingMechanism.h
#        src/rrc/core/NodeMechanism.cpp
#        include/rrc/core/NodeMechanism.h
        src/rrc/core/SettingsMechanism.cpp
        include/rrc/core/SettingsMechanism.h
        src/rrc/core/MechanismVersion.cpp
        include/rrc/core/MechanismVersion.h
#        src/rrc/core/AbstractNode.cpp
        include/rrc/meta.h
        include/rrc/meta/MetaArrayGenerator.h
        include/rrc/core/Serializer.h
        include/rrc/core/Message.h
        include/rrc/core/ArrayReference.h
        include/rrc/core/BigEndian.h
        include/rrc/core/LittleEndian.h
        include/rrc/core/Varint.h
        include/rrc/core/EndianDefines.h
        include/rrc/meta/FunctionTraits.h
        include/rrc/meta/MethodTraits.h
        include/rrc/meta/MetaRename.h
        include/rrc/meta/MetaLength.h
        include/rrc/meta/MetaList.h
        include/rrc/meta/MetaIf.h
        include/rrc/meta/MetaDecay.h
        include/rrc/meta/MetaPushFront.h
        include/rrc/meta/MetaFront.h
        include/rrc/meta/MetaPopFront.h
        include/rrc/meta/MetaClearList.h
        include/rrc/meta/MetaEmpty.h
        include/rrc/meta/MetaTransform.h
        include/rrc/meta/MetaAppend.h
        include/rrc/meta/MetaIntegralSequence.h
        include/rrc/meta/MetaBackSequenceElement.h
        include/rrc/meta/MetaBack.h
        include/rrc/meta/MetaRenameSequence.h
        include/rrc/meta/MetaAppendSequence.h
        include/rrc/meta/MetaPack.h
        include/rrc/meta/MetaPacker.h
        include/rrc/meta/MetaSequenceConcatenator.h
        include/rrc/meta/MetaConcatenator.h
        include/rrc/meta/MetaVarintEncode.h
        include/rrc/core/StructureTypeQuantityGenerator.h
        include/rrc/meta/MetaVarintEncodeSequence.h
        include/rrc/meta/IterationTags.h
        include/rrc/meta/MetaListSize.h
        include/rrc/meta/MetaArrayGenerator.h
        include/rrc/meta/MetaSequenceSize.h
        include/rrc/core/TypesIdentifiersArray.h
        include/rrc/core/TypeSizesArray.h
        include/rrc/meta/ForEachTuple.h
        include/rrc/meta/MetaGenerateSequence.h)

configure_file("${PROJECT_SOURCE_DIR}/template/VersionDefines.h.in"
               "${PROJECT_BINARY_DIR}/VersionDefines.h")



add_library(rrc ${SRCS})
target_link_libraries(rrc variant concurrentqueue)
target_include_directories(rrc PUBLIC include)

if(BUILD_TEST)
    add_subdirectory(test)
endif()