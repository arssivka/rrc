/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include <vector>
#include <future>
#include "NonCopyable.h"
#include "ID.h"

namespace rrc {
    class Scheduler : public NonCopyable {
    public:
        Scheduler(size_t threadsNum);

        int run();

        template <class Func, class... Args>
        void enqueue(const ID& id, Func&& func, Args&&... args);
    private:

    };
}


