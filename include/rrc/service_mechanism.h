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
 *  @date 2/7/17
 */

#pragma once


#include "service_holder.h"
#include "mechanism.h"

namespace rrc {
    template <class Q, class K, class M>
    class service_mechanism : protected mechanism<service_holder<K, M>, Q, 2> {
    public:
        enum {
            SERVICE_CHANGES_PRIORITY,
            SERVICE_CALL_PRIORITY
        };

        typedef K key_type;
        typedef M message_type;
        typedef Q queue_type;
        typedef mechanism<service_holder<key_type, message_type>, queue_type, 2> mechanism_type;
        typedef typename mechanism_type::base_type base_type;
        typedef typename base_type::listener_type listener_type ;
        typedef typename base_type::callback_type callback_type;

        service_mechanism(abstract_launcher& launcher)
                : mechanism_type(launcher) {}

        void add_service(key_type key, std::shared_ptr<callback_type> callback_ptr) {
            this->enqueue_task(
                    SERVICE_CHANGES_PRIORITY,
                    &base_type::add_service,
                    std::move(key),
                    std::move(callback_ptr)
            );
        }

        void remove_service(std::shared_ptr<callback_type> callback_ptr) {
            this->enqueue_task(
                    SERVICE_CHANGES_PRIORITY,
                    &base_type::remove_service,
                    std::move(callback_ptr)
            );
        }

        void call(const key_type& key, message_type input, listener_type listener) {
            this->enqueue_task(
                    SERVICE_CALL_PRIORITY,
                    &base_type::call,
                    std::move(key),
                    std::move(input),
                    std::move(listener)
            );
        }

        std::vector<key_type> keys() const {
            return this->call(&base_type::keys);
        }
    };
}


