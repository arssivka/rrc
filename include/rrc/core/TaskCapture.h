/**
 *  @autor arssivka
 *  @date 2/7/17
 */

#pragma once


#include <functional>

namespace rrc {
    class TaskCapture {
    public:
        TaskCapture(const TaskCapture& capture) = default;

        TaskCapture(TaskCapture&& capture) = default;

        template <class Func, class... Args>
        TaskCapture(Func&& func, Args&&... args)
            : mCallback(std::bind(std::forward<Func>(func), std::forward<Args>(args)...)) {}

        void operator()() {
            mCallback();
        }

    private:
        std::function<void()> mCallback;

    };
}


