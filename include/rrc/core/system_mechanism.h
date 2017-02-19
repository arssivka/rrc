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


#include <memory>
#include <vector>
#include "abstract_launcher.h"
#include "defines.h"
#include "queue_adapter_factory.h"

namespace rrc {
    class system_mechanism {
    public:
        system_mechanism(std::shared_ptr<abstract_queue_adapter<task>> sync_queue,
                         queue_adapter_factory<task>& task_queue_factory,
                         abstract_launcher& launcher,
                         std::vector<std::string> args);

        /**
         * @brief Registers node for the synchronization
         * @param node Pointer to the node, that nees to be registered
         */
        void add_node(std::shared_ptr<node> node);


        /**
         * @brief Unregisters node
         * @param node Pointer to the node that needs to be unregistered
         */
        void remove_node(std::shared_ptr<node> node);

        const std::vector<std::string>& get_args() const;


        /**
        * @brief Stops the launcher from execution
        */
        void stop();


    private:
        std::shared_ptr<abstract_queue_adapter<task>> m_sync_queue;
        abstract_launcher& m_launcher;
        const std::vector<std::string> m_args;
    };
}


