/**
 *  @autor arssivka
 *  @date 7/20/16
 */

#pragma once


#include <atomic>
#include <concurrentqueue.h>
#include "AbstractQueueAdapter.h"

namespace rrc {
    typedef std::function<void()> Task;

    class AbstracrTaskQueueAdapter : public AbstractQueueAdapter<Task> {
    public:
        /**
         * @brief Enques function object with it's args
         * @param func function object
         * @param args Arguments for the function object
         */
         template <class Func, class... Args>
        void enqueueTask(Func&& func, Args... args) {
            this->enqueue(std::bind(std::forward<Func>(func),
                                         std::forward<Args>(args)...));
        }

        /**
         * @brief Executes one Task from queue
         * @return True if succeed otherwise false
         */
        bool execOnce();

        /**
         * @brief Executes all Tasks from queue
         */
        void execAll();
    };
}


