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
 *  @date 11/2/16
 */

#include <rrc/core/mechanisms_holder.h>


rrc::mechanisms_holder::mechanisms_holder(int argc, char** argv, abstract_launcher& launcher,
                                          queue_adapter_factory<task>& queue_adapter_factory)
        : m_launcher(launcher),
          m_system_mechanism_queue((rrc::abstract_task_queue_adapter*) queue_adapter_factory.create()),
          m_advertising_mechanism_queue((rrc::abstract_task_queue_adapter*) queue_adapter_factory.create()),
          m_service_mechanism_queue((rrc::abstract_task_queue_adapter*) queue_adapter_factory.create()),
          m_settings_mechanism_queue((rrc::abstract_task_queue_adapter*) queue_adapter_factory.create()),
          m_system_mechanism(new system_mechanism(m_system_mechanism_queue,
                                                  queue_adapter_factory,
                                                  m_launcher,
                                                  std::vector<std::string>(argv + 1, argv + argc))),
          m_advertising_mechanism(new advertising_mechanism(m_advertising_mechanism_queue,
                                                            queue_adapter_factory)),
          m_service_mechanism(new service_mechanism(m_service_mechanism_queue,
                                                    queue_adapter_factory)),
          m_settings_mechanism(new settings_mechanism(m_settings_mechanism_queue,
                                                      queue_adapter_factory)) {
    m_launcher.add_sync_queue(m_system_mechanism_queue);
    m_launcher.add_sync_queue(m_advertising_mechanism_queue);
    m_launcher.add_sync_queue(m_service_mechanism_queue);
    m_launcher.add_sync_queue(m_settings_mechanism_queue);
}

rrc::mechanisms_holder::~mechanisms_holder() {
    m_launcher.remove_sync_queue(m_system_mechanism_queue);
    m_launcher.remove_sync_queue(m_advertising_mechanism_queue);
    m_launcher.remove_sync_queue(m_service_mechanism_queue);
    m_launcher.remove_sync_queue(m_settings_mechanism_queue);
}


rrc::advertising_mechanism& rrc::mechanisms_holder::get_advertising_mechanism() {
    return *m_advertising_mechanism;
}

rrc::service_mechanism& rrc::mechanisms_holder::get_service_mechanism() {
    return *m_service_mechanism;
}


rrc::settings_mechanism& rrc::mechanisms_holder::get_settings_mechanism() {
    return *m_settings_mechanism;
}


const rrc::advertising_mechanism& rrc::mechanisms_holder::get_advertising_mechanism() const {
    return *m_advertising_mechanism;
}


const rrc::service_mechanism& rrc::mechanisms_holder::get_service_mechanism() const {
    return *m_service_mechanism;
}


const rrc::settings_mechanism& rrc::mechanisms_holder::get_settings_mechanism() const {
    return *m_settings_mechanism;
}
