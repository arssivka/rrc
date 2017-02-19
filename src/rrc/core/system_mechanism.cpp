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

#include <rrc/core/system_mechanism.h>
#include <rrc/core/abstract_task_queue_adapter.h>


rrc::system_mechanism::system_mechanism(std::shared_ptr<abstract_task_queue_adapter> sync_queue,
                                        queue_adapter_factory<task>& task_queue_factory,
                                        abstract_launcher& launcher,
                                        std::vector<std::string> args)
        : m_sync_queue(std::move(sync_queue)), m_launcher(launcher),m_args(std::move(args)) { }


void rrc::system_mechanism::add_node(std::shared_ptr<rrc::node> node) {
    // TODO: Move to enclosure
    auto& launcher = m_launcher;
    m_sync_queue->enqueue([&launcher, node]() {
        launcher.add_node(node);
    });
}


void rrc::system_mechanism::remove_node(std::shared_ptr<rrc::node> node) {
    // TODO: Move to enclosure
    auto& launcher = m_launcher;
    m_sync_queue->enqueue([&launcher, node]() {
        launcher.remove_node(node);
    });
}


void rrc::system_mechanism::stop() {
    m_launcher.stop();
}

const std::vector<std::string>& rrc::system_mechanism::get_args() const {
    return m_args;
}
