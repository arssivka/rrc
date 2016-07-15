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

namespace rrc {
    class Core {
    public:
        Core(int argc, char** argv) : mArgs(&argv[0], &argv[argc]) {}

        int run() {
            return mScheduler.run();
        }

        static Core* instance();

        static constexpr std::string getVersion();

        std::vector<std::string>& getArs() const;

        Settings* getSettings();


    private:
        static Core* sInstance;
        std::vector<std::string> mArgs;
        Scheduler mScheduler;
        Settings mSettings;
    };
}


