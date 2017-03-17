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


#include <vector>
#include <unordered_map>
#include "topic.h"
#include "key_listener.h"

namespace rrc {
    /**
     * @brief Class that contains all the topics and grants access to them.
     */
    class topic_holder {
    public:
        topic_holder();

        void add_topic_listener(const std::string& topic_key,
                                topic_callback callback,
                                const result_callback& result = result_callback());

        // TODO: Docs
        void remove_topic_listener(const std::string& topic_key,
                                   const topic_callback& callback,
                                   const result_callback& result = result_callback());

        void add_key_listener(key_callback callback, const result_callback& result = result_callback());

        void remove_key_listener(const key_callback& callback, const result_callback& result = result_callback());

        void send_message(const std::string& topic_key, const shared_buffer& msg);

        /**
         * @brief Returns set of the keys of registered topics
         * @return Vector of the topics's keys
         */
        std::vector<std::string> keys() const;


    private:
        std::unordered_map<std::string, topic> m_topic_hash;
        key_listener m_key_listener;
    };
}


