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

        void addTopicListener(const std::string& topic, MessageListener* listener);

        void removeTopicListener(const MessageListener* topicListener);

        void addServiceListener(const std::string& service, MessageListener* serviceListener);

        void removeServiceListener(const MessageListener* serviceListener);

    private:
        static Core* sInstance;
        std::vector<std::string> mArgs;
        Scheduler mScheduler;
        Settings mSettings;
    };
}


