/**
 *  @autor arssivka
 *  @date 10/31/16
 */

#pragma once


#include <queue>
#include "AbstractQueueAdapter.h"

namespace rrc {
    template <class T, class Container = std::deque<T>>
    class STLQueueAdapter : public AbstractQueueAdapter<T> {
    public:
        virtual void enqueue(const T& value) override {
            mQueue.emplace(value);
        }


        virtual void enqueue(T&& value) override {
            mQueue.emplace(std::move(value));
        }


        virtual bool tryDequeue(T& value) override {
            if (mQueue.empty())
                return false;
            value = (std::is_move_assignable<T>::value)
                    ? std::move(mQueue.front())
                    : mQueue.front();
            mQueue.pop();
            return true;
        }

    private:
        std::queue<T, Container> mQueue;

    };
}