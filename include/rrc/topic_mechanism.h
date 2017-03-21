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
    class topic_mechanism : protected mechanism<topic_holder, 3> {
    public:
        enum {
            CHANGE_KEY_LISTENERS_PRIORITY,
            CHANGE_TOPIC_LISTENERS_PRIORITY,
            SEND_MESSAGE_PRIORITY
        };


        topic_mechanism(abstract_launcher& launcher);

        /**
         * @brief Send a message
         * @param topic_key Name of the topic for the message
         * @param message Pointer to the message, that needs to be sent
         */
        void send_message(std::string topic_key, shared_buffer message);

        /**
         * @brief Registers listener
         * @param topic_key Name of the topic for the listener
         * @param callback Pointer to the callback that needs to be registered
         */
        void add_topic_listener(std::string topic_key,
                                topic_callback callback,
                                result_callback result = result_callback());

        // TODO Tests and docs
        void remove_topic_listener(std::string topic_key,
                                   topic_callback callback,
                                   result_callback result = result_callback());

        void add_key_listener(key_callback callback,
                              bool get_exists_keys = true,
                              result_callback result = result_callback());

        void remove_key_listener(key_callback callback, result_callback result = result_callback());

        size_t listeners_count(const std::string& topic_key) const;
    };
}


