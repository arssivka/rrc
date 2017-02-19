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
 *  @date 2/2/17
 */

#pragma once


#include <functional>
#include <memory>
#include "abstract_queue_adapter.h"
#include <utility>

namespace rrc {

    // TODO Tests and docs
    template <class T>
    class queue_adapter_factory {
    public:

        template <class I, class... Args>
        static queue_adapter_factory<T> create(Args&&... args) {
            return queue_adapter_factory<T>(type<I>(), args...);
        }


        queue_adapter_factory(queue_adapter_factory&& other) = default;

        queue_adapter_factory(const queue_adapter_factory& other) = default;


        std::unique_ptr<abstract_queue_adapter<T>> create_unique_pointer() const {
            return std::unique_ptr<abstract_queue_adapter<T>>(m_factory_method());
        }

        std::shared_ptr<abstract_queue_adapter<T>> create_shared_pointer() const {
            return std::shared_ptr<abstract_queue_adapter<T>>(m_factory_method());
        }

        abstract_queue_adapter<T>* create() const {
            return m_factory_method();
        }

    private:
        template<class U>
        class type {};

        template <class I, class... Args>
        queue_adapter_factory(type<I>, Args&&... args) {
            static_assert(std::is_base_of<abstract_queue_adapter<T>, I>::value,
                          "Constructed class must be inherited from factory template class");
            m_factory_method = [args...]() -> abstract_queue_adapter<T>* {
                return new I(args...);
            };
        }

        std::function<abstract_queue_adapter<T>*()> m_factory_method;

    };
}