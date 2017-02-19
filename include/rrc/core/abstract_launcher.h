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
 *  @date 7/8/16
 */

#pragma once


#include <memory>
#include "defines.h"

namespace rrc {
    class node;
    template <class T> class abstract_queue_adapter;

    /**
     * @brief Abstract class for creating launchers. Lauуncher is needed to run all the nodes and functionality of the whole system.
     */
    class abstract_launcher {
    public:
        /**
         * @brief Virtual destructor of Abstract Launcher
         */
        virtual ~abstract_launcher() { }

        /**
         * @brief Virtual function for running the launcher
         * @return Status code of pragram state: 0 if succeed
         */
        virtual int run() = 0;

        /**
         * @brief Virtual function for running one step of launcher execution
         * @return True if succeed, otherwise false
         */
        virtual bool step() = 0;

        /**
         * @brief Stops the execution of launcher
         */
        virtual void stop() = 0;

        /**
         * @brief Registers node
         * @param node_ptr Pointer to node instance
         */
        virtual void add_node(std::shared_ptr<node> node_ptr) = 0;

        /**
         * @brief Removes the node from the list
         * @param node_ptr Pointer to node instance
         */
        virtual void remove_node(std::shared_ptr<node> node_ptr) = 0;

        // TODO: Docs and tests
        virtual void add_sync_queue(std::shared_ptr<abstract_queue_adapter<task>> queue_ptr) = 0;

        virtual void remove_sync_queue(std::shared_ptr<abstract_queue_adapter<task>> queue_ptr) = 0;
    };

}


