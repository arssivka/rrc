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
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @autor arssivka
 *  @date 4/8/17
 */

#pragma once


#include "defines.h"
#include <string>
#include <unordered_map>

namespace rrc {
    class sender;
    class receiver;

    class RRC_EXPORT node {
        node(const node&) = delete;

        node& operator=(const node&) = delete;

    public:
        node() = default;

        node(node&&) = default;

        node& operator=(node&&) = default;

        virtual void on_init();

        virtual void on_start();

        virtual void on_finish();

        virtual void on_process();

        virtual ~node();

        void add_sender(const std::string& key,
                        sender* sender_ptr);

        void add_receiver(const std::string& key,
                          receiver* receiver_ptr);

        sender* find_sender(const std::string& key) const noexcept;

        receiver* find_receiver(const std::string& key) const noexcept;

    private:
        std::unordered_map<std::string, sender*> m_senders_hash;
        std::unordered_map<std::string, receiver*> m_receivers_hash;

    };
}


