/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include "NonCopyable.h"
#include "AbstracrTaskQueueAdapter.h"
#include "MechanismsHolder.h"

namespace rrc {
    /**
     * @brief Abstract class for creating nodes - modules of the system. Each module holds it's own functionality.
     * In the terms of the system, node - is atomic. Execution of it's entry is guaranteed.
     */
    class Node : private NonCopyable {
    public:
        // TODO: Tests and docs
        Node(std::shared_ptr<AbstracrTaskQueueAdapter> taskQueue, MechanismsHolder& mechanismsHolder);

        const std::weak_ptr<TaskHub> subscribe(const std::string& topicName,
                                                       TaskHub::Callback&& callback);

        void unsubscribe(const std::string& topicName, const std::weak_ptr<TaskHub> listener);

        void sendMessage(const std::string& topic, std::shared_ptr<Buffer> message);

        virtual void entry();

        /**
         * @brief Virtual destructor of AbstractNode
         */
        virtual ~Node();

    private:
        std::shared_ptr<AbstracrTaskQueueAdapter> mTaskQueue;
        MechanismsHolder& mMechanismsHolder;
    };
}


