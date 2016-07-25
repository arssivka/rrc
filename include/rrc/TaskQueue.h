/**
 *  @autor arssivka
 *  @date 7/20/16
 */

#pragma once


#include <atomic>
#include "TSQueue.h"

namespace rrc {
    class TaskQueue {
    public:
        typedef std::shared_ptr<TaskQueue> SPtr;

        template <class Func, class... Args>
        void enqueue(Func&& func, Args... args) {
            if (this->isDisabled()) return;
            mTaskQueue.push(std::bind(std::forward<Func>(func), std::forward<Args>(args)));
        }

        void execOnce();

        void execAll();

        void disable();

        bool isDisabled() const;

    private:
        typedef TSQueue<std::function<void()>> TSFunctionQueue;

        TSFunctionQueue mTaskQueue;
        std::atomic<bool> mDisabled;
    };
}


