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
 *  @date 8/24/16
 */

#pragma once


#include <list>
#include "task_packer.h"
#include "defines.h"

namespace rrc {
    /**
     * @brief All messages come to topics. Topic is a special place for holding specific messages. Nodes can subscribe to tpoics to get messages they need.
     */
    class topic {
    public:
        using message_type = cow_string;
        using subscriber_type = task_packer<message_type>;

        /**
         * @brief Register message listener
         * @param listener Pointer to listener to register
         */
        void add_listener(std::shared_ptr<subscriber_type> listener_ptr);

        // TODO: Docs
        void remove_listener(std::shared_ptr<subscriber_type> listener_ptr);

        /**
         * @brief Sends the message
         * @param message Pointer to message that needs to be sent
         */
        void send_message(message_type message);

        /**
         * @brief Checks if this topic has listeners
         * @return True if topic has lesteners, otherwise false
         */
        bool has_listeners() const;

    private:
        std::list<std::shared_ptr<subscriber_type>> m_listeners_list;
    };
}


