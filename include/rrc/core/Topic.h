/**
 *  @autor arssivka
 *  @date 8/24/16
 */

#pragma once


#include <forward_list>
#include "MessageListener.h"
#include "NonCopyable.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    class Topic {
    public:
        Topic(TypeId id);

        bool addListener(MessageListenerPtr listener);

        void removeListener(MessageListenerPtr listener);

        void sendMessage(MessagePtr message);

        TypeId getTypeId() const noexcept;

        bool checkCapability(TypeId typeId) const noexcept;

        bool empty() const;

    private:
        TypeId mTypeId;
        std::forward_list<MessageListenerPtr> mListenersList;

    };

    typedef std::shared_ptr<Topic> TopicPtr;
}


