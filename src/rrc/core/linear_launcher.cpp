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

#include <rrc/core/linear_launcher.h>
#include <stdlib.h>


rrc::linear_launcher::linear_launcher()
        : m_finished(false) { }


rrc::linear_launcher::~linear_launcher() { }


int rrc::linear_launcher::run() {
    m_finished = false;
    while (this->step());
    return EXIT_SUCCESS;
}


void rrc::linear_launcher::stop() {
    m_finished = true;
}


void rrc::linear_launcher::add_node(std::shared_ptr<rrc::node> node) {
    m_nodes_list.emplace_front(std::move(node));
}


void rrc::linear_launcher::remove_node(std::shared_ptr<rrc::node> node) {
    m_nodes_list.remove(node);
}


bool rrc::linear_launcher::step() {
    if (m_finished) return false;
    for (auto&& queue : m_queues_list) queue->exec_all();
    for (auto&& node : m_nodes_list) node->entry();
    return m_finished;
}


void rrc::linear_launcher::add_sync_queue(std::shared_ptr<abstract_task_queue_adapter> queue) {
    m_queues_list.emplace_front(std::move(queue));
}


void rrc::linear_launcher::remove_sync_queue(std::shared_ptr<abstract_task_queue_adapter> queue) {
    m_queues_list.remove(queue);
}
