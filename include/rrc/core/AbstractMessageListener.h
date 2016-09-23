/**
 *  @autor arssivka
 *  @date 9/23/16
 */

#pragma once


#include "Message.h"


namespace rrc {
    class AbstractMessageListener {
    public:
        /**
         * @brief Adds message to queue
         * @param msg Pointer to desired message
         */
        virtual void enqueueMessage(MessagePtr msg) = 0;

        /**
         * @brief Tries to dequeue message from queue
         * @return Pointer to message
         */
        virtual MessagePtr tryDequeueMessage() = 0;

        /**
         * @brief Returns type id of messages that of this message listener
         * @return
         */
        TypeId getTypeId() const;

    protected:
        /**
         * @brief Constructor of Message Listener
         * @param typeId Type id of messages to listen
         */
        AbstractMessageListener(TypeId typeId);

    private:
        TypeId mTypeId;

    };

    typedef std::shared_ptr<AbstractMessageListener> AbstractMessageListenerPtr;
}