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
 *  @date 11/5/16
 */

#pragma once


#include <vector>
#include "topic_holder.h"
#include "queue_adapter_factory.h"

namespace rrc {
    class advertising_mechanism : private non_copyable {
    public:
        using key_type = std::string;
        using subscriber = topic_holder<key_type>::subscriber_type;
        using message = topic::message_type;


        advertising_mechanism(std::shared_ptr<abstract_queue_adapter<task>> sync_queue,
                              queue_adapter_factory<task>& task_queue_factory);

        /**
         * @brief Send a message
         * @param topicName Name of the topic for the message
         * @param message Pointer to the message, that needs to be sent
         */
        void send_message(key_type key, message message) {
            m_messages_queue->enqueue([this, key_cap = std::move(key),
                                              message_cap = std::move(message)]() mutable {
                m_topic_holder.send_message(key_cap, std::move(message_cap));
            });
            this->enqueue_update();
        }

        /**
         * @brief Registers listener
         * @param topicName Name of the topic for the listener
         * @param listenerPtr Pointer to the listener that needs to be registered
         */
        void add_listener(key_type key, std::shared_ptr<subscriber> listener_ptr) {
            m_listeners_queue->enqueue([this, key_cap = std::move(key),
                                               listener_ptr_cap = std::move(listener_ptr)]() mutable {
                m_topic_holder.add_listener(key_cap, std::move(listener_ptr_cap));
            });
            this->enqueue_update();
        }

        // TODO Tests and docs
        void removeListener(key_type key, const std::shared_ptr<subscriber> listener_ptr) {
            m_listeners_queue->enqueue([this, key_cap = std::move(key),
                                             listener_ptr_cap = std::move(listener_ptr)]() mutable {
                m_topic_holder.remove_listener(key_cap, std::move(listener_ptr_cap));
            });
            this->enqueue_update();
        }

        /**
         * @brief Returns set of avaliable topic names
         * @return Set of topic names
         */
        std::vector<key_type> keys() const;

    private:
        void enqueue_update();

        void apply_queues();

    private:
        topic_holder<key_type> m_topic_holder;
        std::shared_ptr<abstract_queue_adapter<task>> m_sync_queue;
        std::unique_ptr<abstract_queue_adapter<task>> m_listeners_queue;
        std::unique_ptr<abstract_queue_adapter<task>> m_messages_queue;
        std::atomic_flag m_changes_enqueued_flag;
    };
}


