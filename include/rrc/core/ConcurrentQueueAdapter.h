/**
 *  @autor arssivka
 *  @date 10/31/16
 */

#pragma once

#include <concurrentqueue.h>
#include "AbstractQueueAdapter.h"

namespace rrc {
    template <class T>
    class ConcurrentQueueAdapter : public AbstractQueueAdapter<T> {
    public:
        virtual void enqueue(const T& value) override {
            mQueue.enqueue(value);
        }

        virtual void enqueue(T&& value) override {
            mQueue.enqueue(std::forward<T>(value));
        }

        virtual bool tryDequeue(T& value) override {
            return mQueue.try_dequeue(value);
        }

    private:
        moodycamel::ConcurrentQueue<T> mQueue;

    };
}