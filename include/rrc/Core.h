/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include <vector>
#include <string>
#include <memory>
#include "Settings.h"
#include "Scheduler.h"
#include "MessageListener.h"
#include "MessageSender.h"
#include "TSLookUp.h"
#include "TopicConnector.h"
#include "ServiceConnector.h"
#include "TSQueue.h"
#include "TaskQueue.h"

namespace rrc {
    class Core {
    public:
        typedef std::string Key;

        Core(size_t threadsNum, int argc, char** argv)
                : mArgs(&argv[0], &argv[argc]), mScheduler(threadsNum) {}

        int run() {
            return mScheduler.run();
        }

        static Core* instance();

        static constexpr std::string getVersion();

        std::vector<std::string>& getArs() const;

        Settings* getSettings();

        bool addTopicListener(const ID& id, const Key& topic, MessageListener::SPtr listener);

        bool detachTopicListener(const Key& topic, const MessageListener::SPtr listener);

        bool addTopicSender(const ID& id, const Key& topic, MessageSender::SPtr sender);

        bool detachTopicSender(const Key& topic, const MessageSender::SPtr sender);

        bool setServiceStuff(const ID& id, const Key& service, MessageStuff::SPtr stuff);

        bool detachServiceStuff(const Key& service, const MessageStuff::SPtr stuff);

        bool addClientStuff(const ID& id, const Key& service, MessageStuff::SPtr stuff);

        bool detachClientStuff(const Key& service, const MessageStuff::SPtr stuff);

        TaskQueue::SPtr getTaskQueue(const ID& id) const;

        bool deleteTaskQueue(const ID& id);

    private:
        typedef TSLookUp<Key, TopicConnector> TopicsContainer;
        typedef TSLookUp<Key, ServiceConnector> ServicesContainer;
        typedef TSLookUp<ID, TaskQueue> TaskQueueContainer;

        static Core* sInstance;
        std::vector<std::string> mArgs;
        Scheduler mScheduler;
        Settings mSettings;

        TopicsContainer mTopics;
        ServicesContainer mServices;
        mutable TaskQueueContainer mTasks;

    };
}


