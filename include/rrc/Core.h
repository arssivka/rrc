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

        bool addTopicListener(const ID& id, const Key& topic, MessageListener* listener, bool directCallEnabled);

        bool detachTopicListener(const Key& topic, const MessageListener* listener);

        bool addTopicSender(const Key& topic, MessageSender* sender);

        bool detachTopicSender(const Key& topic, const MessageSender* sender);

        bool setServiceStuff(const ID& id, const Key& service, MessageStuff* stuff, bool directCallEnabled);

        bool detachServiceStuff(const Key& service, const MessageStuff* stuff);

        bool addClientStuff(const ID& id, const Key& service, MessageStuff* stuff);

        bool detachClientStuff(const Key& service, const MessageStuff* stuff);

        void setDirectCallEnabled(bool state);

        bool isDirectCallEnabled() const;

    private:
        typedef TSLookUp<Key, TopicConnector> TopicsContainer;
        typedef TSLookUp<Key, ServiceConnector> ServicesContainer;

        static Core* sInstance;
        std::vector<std::string> mArgs;
        Scheduler mScheduler;
        Settings mSettings;

        TopicsContainer mTopics;
        ServicesContainer mServices;



        bool mDirectCallEnabled;
    };
}


