/**
 *  @autor tekatod
 *  @date 2/2/17
 */
#pragma once

#include <queue>
#include "rrc/core/AbstractQueueAdapter.h"

template<class T>
class QueueAdapter : public rrc::AbstractQueueAdapter<T> {
public:
    QueueAdapter() = default;
    void enqueue(const T& value) {
        mQueue.emplace(value);
    }

    void enqueue(T&& value) {
        mQueue.emplace(value);
    }

    bool tryDequeue(T& value) {
        return mQueue.empty();
    }

private:
    std::queue<T> mQueue;
};