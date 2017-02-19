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
 *  @date 8/26/16
 */

#pragma once


#include <forward_list>
#include "abstract_launcher.h"
#include "node.h"

namespace rrc {
    /**
     * @brief This launcher implimentation uses only one thread to run all the nodes.
     */
    class linear_launcher : public abstract_launcher {
    public:
        /**
         * @brief Default constructor of Linear Launcher
         */
        linear_launcher();

        /**
         * @brief Linear Launcher destructor
         */
        virtual ~linear_launcher() override;

        /**
        * @brief Virtual function for running the launcher
        * @return Status code of pragram state: 0 if succeed
        */
        virtual int run() override;

        /**
        * @brief Virtual function for running one step of launcher execution
        * @return True if succeed, otherwise false
        */
        virtual bool step() override;

        /**
         * @brief Stops the execution of launcher
         */
        virtual void stop() override;

        /**
        * @brief Registers node
        * @param node Pointer to node instance
        */
        virtual void add_node(std::shared_ptr<node> node) override;

        /**
         * @brief Removes the node from the list
         * @param node Pointer to node instance
         */
        virtual void remove_node(std::shared_ptr<node> node) override;

        virtual void add_sync_queue(std::shared_ptr<abstract_task_queue_adapter> queue) override;

        virtual void remove_sync_queue(std::shared_ptr<abstract_task_queue_adapter> queue) override;

    private:
        bool m_finished;
        std::forward_list<std::shared_ptr<node>> m_nodes_list;
        std::forward_list<std::shared_ptr<abstract_task_queue_adapter>> m_queues_list;
    };
}


