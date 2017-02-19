/**
 * Copyright 2016 Arseniy Ivin <arssivka@yandex.ru>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @autor arssivka
 *  @date 10/31/16
 */

#pragma once

#include <concurrentqueue.h>
#include "abstract_queue_adapter.h"

namespace rrc {
    template <class T>
    class concurrent_queue_adapter : public abstract_queue_adapter<T> {
    public:
        virtual void enqueue(const T& value) override {
            mQueue.enqueue(value);
        }

        virtual void enqueue(T&& value) override {
            mQueue.enqueue(std::forward<T>(value));
        }

        virtual bool try_dequeue(T& value) override {
            return mQueue.try_dequeue(value);
        }

    private:
        moodycamel::ConcurrentQueue<T> mQueue;
    };
}