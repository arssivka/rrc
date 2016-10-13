/**
 *  @autor nikitas
 *  @date 10/7/16
 */
#include "rrc/io/IOService.h"

void rrc::IOService::run() {
    while (true)
    {
        if (mAsyncCommandQueue.size() > 0)
        {
            auto func = mAsyncCommandQueue.front();
            func();
            mAsyncCommandQueue.pop();
        }
    }
}

void rrc::IOService::addAsyncCommand(rrc::AsyncCommand &&command) {
    mAsyncCommandQueue.push(command);
}
