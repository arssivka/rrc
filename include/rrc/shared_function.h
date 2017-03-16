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
 *  @date 3/16/17
 */
#pragma once


#include <memory>
#include <functional>

namespace rrc {
    template <class F>
    class shared_function {
    public:
        typedef std::function<F> function_type;

        shared_function(const function_type& function)
                : m_functor_ptr(std::make_shared<function_type>(function)) {}

        shared_function(function_type&& function)
                : m_functor_ptr(std::make_shared<function_type>(std::move(function))) {}

        shared_function(std::shared_ptr<function_type> function_ptr)
                : m_functor_ptr(std::move(function_ptr)) {}

        shared_function(const shared_function&) = default;

        shared_function(shared_function&&) = default;

        template <class... Args>
        auto operator()(Args&&... args) const -> typename function_type::result_type {
            function_type& functor = *m_functor_ptr;
            return functor(std::forward<Args>(args)...);
        }

        bool operator==(const shared_function& rhs) const {
            return m_functor_ptr == rhs.m_functor_ptr;
        }

        bool operator!=(const shared_function& rhs) const {
            return !(rhs == *this);
        }

        function_type* get() const noexcept {
            return m_functor_ptr.get();
        }

    private:
        std::shared_ptr<function_type> m_functor_ptr;
    };
}

namespace std {
    template <class F>
    struct hash<rrc::shared_function<F>> {
        typedef rrc::shared_function<F> argument_type;
        typedef std::size_t result_type;

        size_t operator()(const argument_type& arg) const {
            typedef argument_type::function_type function_type;
            return std::hash<function_type*>{}(arg.get());
        }
    };
}

