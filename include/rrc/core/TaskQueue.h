/**
 *  @autor arssivka
 *  @date 7/20/16
 */

#pragma once


#include <atomic>
#include <concurrentqueue.h>

namespace rrc {
    typedef std::function<void()> Task;

    class TaskQueue {
    public:
        template <class Func, class... Args>
        void enqueue(Func&& func, Args... args) {
            mTaskQueue.enqueue(std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
        }

        void enqueue(const Task& task) {
            mTaskQueue.enqueue(task);
        }

        void enqueue(Task&& task) {
            mTaskQueue.enqueue(std::move(task));
        }

        bool tryDequeue(Task& task);

        bool execOnce();

        void execAll();

    private:
        moodycamel::ConcurrentQueue<Task> mTaskQueue;

    };
}


