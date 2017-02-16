/**
 *  @autor arssivka
 *  @date 2/7/17
 */

#include "include/rrc/core/Service.h"


rrc::Service::Service(std::weak_ptr<rrc::AbstractTaskQueueAdapter> taskQueue, const rrc::Service::Callback& callback)
        : mTaskQueue(std::move(taskQueue)), mCallback(callback) {}


rrc::Service::Service(std::weak_ptr<rrc::AbstractTaskQueueAdapter> taskQueue, rrc::Service::Callback&& callback)
        : mTaskQueue(std::move(taskQueue)), mCallback(std::move(callback)) {}


void rrc::Service::call(std::shared_ptr<TaskHub<Buffer>> resultHub, std::shared_ptr<rrc::Buffer> input) {
    auto& callback = mCallback;
    auto taskQueue = mTaskQueue.lock();
    if (taskQueue != nullptr) {
        taskQueue->enqueue(
                [&callback, capturedTaskHub = std::move(resultHub), capturedInput = std::move(input)]() mutable {
                    try {
                        auto result = callback(*capturedInput);
                        capturedTaskHub->enqueueTask(result);
                    } catch (...) {
                        capturedTaskHub->enqueueTask(nullptr);
                    }
                });
    } else {
        resultHub->enqueueTask(nullptr);;
    }
}
