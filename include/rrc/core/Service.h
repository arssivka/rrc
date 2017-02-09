/**
 *  @autor arssivka
 *  @date 2/7/17
 */

#pragma once


#include <memory>
#include <functional>
#include <future>
#include "TaskHub.h"

namespace rrc {
    // TODO Tests and docs
    class Service {
    public:
        typedef std::function<std::shared_ptr<Buffer>(const Buffer&)> Callback;

        Service(std::weak_ptr<AbstracrTaskQueueAdapter> taskQueue, const Callback& callback);

        Service(std::weak_ptr<AbstracrTaskQueueAdapter> taskQueue, Callback&& callback);

        void call(std::shared_ptr<TaskHub> resultHub, std::shared_ptr<Buffer> input);

    private:
        std::weak_ptr<AbstracrTaskQueueAdapter> mTaskQueue;
        Callback mCallback;
    };
}


