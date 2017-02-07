/**
 *  @autor arssivka
 *  @date 8/24/16
 */

#pragma once


#include <list>
#include <memory>
#include "MessageListener.h"
#include "NonCopyable.h"

namespace rrc {
    /**
     * @brief All messages come to topics. Topic is a special place for holding specific messages. Nodes can subscribe to tpoics to get messages they need.
     */
    class Topic {
    public:
        /**
         * @brief Default constructor of Topic
         */
        Topic() = default;

        /**
         * @brief Register message listener
         * @param listener Pointer to listener to register
         */
        void addListener(std::shared_ptr<MessageListener> listener);

        // TODO: Docs
        void removeListener(std::weak_ptr<MessageListener> listener);

        /**
         * @brief Sends the message
         * @param message Pointer to message that needs to be sent
         */
        void sendMessage(std::shared_ptr<Buffer> message);

        /**
         * @brief Checks if this topic has listeners
         * @return True if topic has lesteners, otherwise false
         */
        bool hasListeners() const;

    private:
        std::list<std::shared_ptr<MessageListener>> mListenersList;
    };
}


