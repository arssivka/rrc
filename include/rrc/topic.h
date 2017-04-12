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
 *  @date 4/11/17
 */

#pragma once


#include <forward_list>

namespace rrc {
    class sender;
    class receiver;

    class topic {
    public:
        void add_sender(sender* sender_ptr);

        void add_receiver(receiver* receiver_ptr);

        void reset();

        void connect();

    private:
        std::forward_list<sender*> m_senders;
        std::forward_list<receiver*> m_receivers;
    };
}


