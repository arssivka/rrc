/**
 *  @autor nikitas
 *  @date 10/7/16
 */
#pragma once

#include <queue>
#include <functional>

#include "Definitions.h"

namespace rrc
{
    typedef std::function<void()> AsyncCommand;

    class IOService
    {
    public:
        void run();
        void addAsyncCommand(AsyncCommand &&command);
    private:
        std::queue<AsyncCommand> mAsyncCommandQueue;
    };
}


