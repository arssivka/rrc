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

        /**
         * @brief Enques function object with it's args
         * @param func function object
         * @param args Arguments for the function object
         */
        template <class Func, class... Args>
        void enqueue(Func&& func, Args... args) {
            mTaskQueue.enqueue(std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
        }

        /**
         * @brief Enques const Task
         * @param task const reference to  Task - function<void> object
         */
        void enqueue(const Task& task) {
            mTaskQueue.enqueue(task);
        }

        /**
         * @brief Enques Task by moving
         * @param task function<void> object
         */
        void enqueue(Task&& task) {
            mTaskQueue.enqueue(std::move(task));
        }

        /**
         * @brief Tries to deque Task into specified reference
         * @param task reference to Task - function<void> object
         * @return True if succeed otherwise false
         */
        bool tryDequeue(Task& task);

        /**
         * @brief Executes one Task from queue
         * @return True if succeed otherwise false
         */
        bool execOnce();

        /**
         * @brief Executes all Tasks from queue
         */
        void execAll();

    private:
        moodycamel::ConcurrentQueue<Task> mTaskQueue;

    };
}


