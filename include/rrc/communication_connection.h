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
 *  @date 4/13/17
 */

#pragma once


#include <string>

namespace rrc {
    class communication_connection {
    public:
        communication_connection() = default;

        communication_connection(const std::string& src_node,
                                 const std::string& sender,
                                 const std::string& dst_node,
                                 const std::string& receiver);

        const std::string& src_node() const;

        void set_src_node(const std::string& src_node);

        const std::string& sender() const;

        void set_sender(const std::string& sender);

        const std::string& dst_node() const;

        void set_dst_node(const std::string& dst_node);

        const std::string& receiver() const;

        void set_receiver(const std::string& receiver);

    private:
        std::string m_src_node;
        std::string m_sender;
        std::string m_dst_node;
        std::string m_receiver;
    };
}


