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
 *  @date 9/23/16
 */

#pragma once


#include <memory>
#include "abstract_task_queue_adapter.h"

namespace rrc {
    template <class T>
    class task_packer {
    public:
        typedef T type;
        typedef std::function<void(type)> callback_type;

        // TODO Tests and docs
        task_packer(std::weak_ptr<abstract_task_queue_adapter> task_queue_ptr, callback_type&& callback)
                : m_task_queue_ptr(std::move(task_queue_ptr)), m_callback(std::move(callback)) {}

        task_packer(std::weak_ptr<abstract_task_queue_adapter> task_queue_ptr, const callback_type& callback)
                : m_task_queue_ptr(task_queue_ptr), m_callback(callback) {}

        bool is_orphan() const {
            return m_task_queue_ptr.use_count() == 0;
        }

        bool enqueue_task(const T& message) {
            auto queue = m_task_queue_ptr.lock();
            if (queue != nullptr) {
                auto& callback = m_callback;
                queue->enqueue([callback, message]() {
                    callback(message);
                });
                return true;
            } else {
                return false;
            }
        }

        bool enqueue_task(T&& message) {
            auto queue = m_task_queue_ptr.lock();
            if (queue != nullptr) {
                auto& callback = m_callback;
                queue->enqueue([callback, message_cap = std::move(message)]() mutable {
                    callback(std::move(message_cap));
                });
                return true;
            } else {
                return false;
            }
        }

        bool operator()(const T& message) {
            return this->enqueue_task(message);
        }

        bool operator()(T&& message) {
            return this->enqueue_task(std::move(message));
        }

        /**
         * @brief Virtual destructor of AbstractMessageListener
         */
        ~task_packer() {}

    private:
        std::weak_ptr<abstract_task_queue_adapter> m_task_queue_ptr;
        callback_type m_callback;

    };
}