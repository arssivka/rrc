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
        typedef std::shared_ptr<Topic> Ptr;

        Topic(TypeId id);

        bool addListener(MessageListener::Ptr listener);

        void removeListener(MessageListener::Ptr listener);

        void sendMessage(Message::Ptr message);

        TypeId getTypeId() const noexcept;

        bool checkCapability(TypeId typeId) const noexcept;

        bool empty() const;

    private:
        TypeId mTypeId;
        std::forward_list<MessageListener::Ptr> mListenersList;

    };
}


