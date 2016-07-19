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
        Core(size_t threadsNum, int argc, char** argv)
                : mArgs(&argv[0], &argv[argc]), mScheduler(threadsNum) {}

        int run() {
            return mScheduler.run();
        }

        static Core* instance();

        static constexpr std::string getVersion();

        std::vector<std::string>& getArs() const;

        Settings* getSettings();

        bool addTopicListener(const ID& id, const std::string& topic,
                              MessageListener* listener, bool directCallEnabled);

        bool detachTopicListener(const MessageListener* listener);

        bool addTopicSender(const std::string& topic, MessageSender* sender);

        bool detachTopicSender(const MessageSender* sender);

        bool addServiceStuff(const ID& id, const std::string& service, MessageStuff* stuff, bool directCallEnabled);

        bool detachServiceStuff(const MessageStuff* stuff);

        bool addClientStuff(const std::string& service, MessageStuff* stuff);

        bool detachClientStuff(const MessageStuff* stuff);

        void setDirectCallEnabled(bool state) {
            mDirectCallEnabled = true;
        }

        bool isDirectCallEnabled() const {
            return  mDirectCallEnabled;
        }

    private:
        static Core* sInstance;
        std::vector<std::string> mArgs;
        Scheduler mScheduler;
        Settings mSettings;

        TSLookUp<std::string, TopicConnector> mTopics;
        TSLookUp<std::string, ServiceConnector> mServices;

        bool mDirectCallEnabled;
    };
}


