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


#include "topic_holder.h"
#include "mechanism.h"

namespace rrc {
    class advertising_mechanism : protected mechanism<topic_holder, 2> {
    public:
        enum {
            CHANGE_LISTENERS_PRIORITY,
            SEND_MESSAGE_PRIORITY
        };


        advertising_mechanism(abstract_launcher& launcher)
                : mechanism(launcher) {}

        /**
         * @brief Send a message
         * @param topic_key Name of the topic for the message
         * @param message Pointer to the message, that needs to be sent
         */
        void send_message(std::string topic_key, shared_buffer message) {
            mechanism::template enqueue_task<SEND_MESSAGE_PRIORITY>(
                    &base_type::send_message,
                    std::move(topic_key),
                    std::move(message)
            );
        }

        /**
         * @brief Registers listener
         * @param topic_key Name of the topic for the listener
         * @param callback Pointer to the callback that needs to be registered
         */
        void add_listener(std::string topic_key, topic_callback callback) {
            mechanism::template enqueue_task<CHANGE_LISTENERS_PRIORITY>(
                    &base_type::add_listener,
                    std::move(topic_key),
                    std::move(callback)
            );
        }

        // TODO Tests and docs
        void remove_listener(std::string topic_key, topic_callback callback) {
            mechanism::template enqueue_task<CHANGE_LISTENERS_PRIORITY>(
                    &base_type::remove_listener,
                    std::move(topic_key),
                    std::move(callback)
            );
        }

        /**
         * @brief Returns set of avaliable topic names
         * @return Set of topic names
         */
        std::vector<std::string> keys() const {
            return mechanism::call(mem_fn(&base_type::keys));
        }

    };
}


