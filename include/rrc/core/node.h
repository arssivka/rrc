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


#include "non_copyable.h"
#include "exec.h"
#include "mechanisms_holder.h"

namespace rrc {
    /**
     * @brief Abstract class for creating nodes - modules of the system. Each module holds it's own functionality.
     * In the terms of the system, node - is atomic. Execution of it's entry is guaranteed.
     */
    class node : private non_copyable {
    public:
        using subscriber_type = typename advertising_mechanism::subscriber;
        using subscriber_callback_type = typename subscriber_type::callback_type;
        using topic_key_type = typename advertising_mechanism::key_type;
        using topic_message_type = typename advertising_mechanism::message;

        using service_key_type = typename service_mechanism::key_type;
        using service_message_type = typename service_mechanism::message_type;
        using service_listener_type = typename service_mechanism::listener_type;
        using service_callback_type = typename service_mechanism::callback_type;

        using settings_key_type = typename settings_mechanism::key_type;
        using settings_listener_type = typename settings_mechanism::listener_type;

        // TODO: Tests and docs
        node(std::shared_ptr<abstract_queue_adapter<task>> task_queue, mechanisms_holder& mechanisms_holder);

        std::shared_ptr<subscriber_type> subscribe(topic_key_type key,
                                                   subscriber_callback_type callback);

        void unsubscribe(topic_key_type key, std::shared_ptr<subscriber_type> listener_ptr);

        void send_message(topic_key_type key, topic_message_type message) {
            auto& mechanism = m_mechanisms_holder.get_advertising_mechanism();
            mechanism.send_message(std::move(key), std::move(message));
        }

        std::shared_ptr<service> add_service(service_key_type key,
                                             service_callback_type callback);

        void remove_service(service_key_type key, std::shared_ptr<service> service_ptr);

        void call(service_key_type key, service_message_type message,
                  service_listener_type::callback_type callback) {
            auto& mechanism = m_mechanisms_holder.get_service_mechanism();
            auto listener = std::make_shared<service_listener_type>(m_task_queue_ptr, std::move(callback));
            mechanism.call(std::move(key), std::move(listener), std::move(message));
        }


        bool try_get_property(const settings_key_type& key, property& output) const;

        void set_property(settings_key_type key, property prop);

        std::shared_ptr<settings_listener_type> add_settings_listener(settings_key_type key,
                                                                      settings_listener_type::callback_type callback);

        void remove_settings_listener(settings_key_type key,
                                      std::shared_ptr<settings_listener_type> listener_ptr);

        virtual void before_events();

        virtual void after_events();

        virtual void entry();

        const std::string& name() const;

        void set_name(const std::string& name);

        /**
         * @brief Virtual destructor of AbstractNode
         */
        virtual ~node();

    protected:
        std::shared_ptr<abstract_queue_adapter<task>> task_queue() const;

    private:
        std::shared_ptr<abstract_queue_adapter<task>> m_task_queue_ptr;
        mechanisms_holder& m_mechanisms_holder;
        std::string m_name;
    };
}


