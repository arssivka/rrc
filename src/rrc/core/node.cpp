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
 *  @date 11/21/16
 */

#include <rrc/core/node.h>


rrc::node::node(std::shared_ptr<rrc::abstract_queue_adapter<rrc::task>> task_queue,
                rrc::mechanisms_holder& mechanisms_holder)
        : m_task_queue_ptr(std::move(task_queue)), m_mechanisms_holder(mechanisms_holder) {}


std::shared_ptr<rrc::node::subscriber_type>
rrc::node::subscribe(rrc::node::topic_key_type key, rrc::node::subscriber_callback_type callback) {
    auto& mechanism = m_mechanisms_holder.get_advertising_mechanism();
    auto subscriber_ptr = std::make_shared<subscriber_type>(m_task_queue_ptr, std::move(callback));
    mechanism.add_listener(std::move(key), subscriber_ptr);
    return subscriber_ptr;
}


void rrc::node::unsubscribe(rrc::node::topic_key_type key, std::shared_ptr<rrc::node::subscriber_type> listener_ptr) {
    auto& mechanism = m_mechanisms_holder.get_advertising_mechanism();
    mechanism.remove_listener(std::move(key), std::move(listener_ptr));
}


std::shared_ptr<rrc::service>
rrc::node::add_service(rrc::node::service_key_type key, rrc::node::service_callback_type callback) {
    auto& mechanism = m_mechanisms_holder.get_service_mechanism();
    auto listener = std::make_shared<service>(m_task_queue_ptr, std::move(callback));
    mechanism.add_service(std::move(key), listener);
    return listener;
}


void rrc::node::remove_service(rrc::node::service_key_type key, std::shared_ptr<rrc::service> service_ptr) {
    auto& mechanism = m_mechanisms_holder.get_service_mechanism();
    mechanism.add_service(std::move(key), std::move(service_ptr));
}


bool rrc::node::try_get_property(const rrc::node::settings_key_type& key, rrc::property& output) const {
    auto& mechanism = m_mechanisms_holder.get_settings_mechanism();
    return mechanism.try_get_property(key, output);
}


void rrc::node::set_property(rrc::node::settings_key_type key, rrc::property prop) {
    auto& mechanism = m_mechanisms_holder.get_settings_mechanism();
    mechanism.set_property(std::move(key), std::move(prop));
}


std::shared_ptr<rrc::node::settings_listener_type> rrc::node::add_settings_listener(rrc::node::settings_key_type key,
                                                                                    rrc::task_packer<rrc::property>::callback_type callback) {
    auto& mechanism = m_mechanisms_holder.get_settings_mechanism();
    auto listener_ptr = std::make_shared<settings_listener_type>(m_task_queue_ptr, std::move(callback));
    mechanism.add_listener(std::move(key), listener_ptr);
    return listener_ptr;
}


void rrc::node::remove_settings_listener(rrc::node::settings_key_type key,
                                         std::shared_ptr<rrc::node::settings_listener_type> listener_ptr) {
    auto& mechanism = m_mechanisms_holder.get_settings_mechanism();
    mechanism.add_listener(std::move(key), std::move(listener_ptr));
}


void rrc::node::before_events() {}


void rrc::node::after_events() {}


void rrc::node::entry() {
    this->before_events();
    exec_all(m_task_queue_ptr);
    this->after_events();
}


const std::string& rrc::node::name() const {
    return m_name;
}


void rrc::node::set_name(const std::string& name) {
    m_name = name;
}


rrc::node::~node() {}


std::shared_ptr<rrc::abstract_queue_adapter<rrc::task>> rrc::node::task_queue() const {
    return m_task_queue_ptr;
}
