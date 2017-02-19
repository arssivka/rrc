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
 *  @date 7/18/16
 */

#pragma once


#include <memory>

namespace rrc {
    /**
     * @brief Class that makes his child classes to be copied only when modified.
     */
    template <class T>
    class copy_on_write {
    public:
        typedef T type;

        template <class... Args>
        copy_on_write(Args... args)
                : m_data(std::make_shared<type>(std::forward<Args>(args)...)) {}

        copy_on_write(T* data = nullptr)
                : m_data(data) {
        }

        copy_on_write(std::shared_ptr<T> sptr)
                : m_data(std::move(sptr)) {
        }

        const T& operator*() const {
            this->ensure_initialized();
            return *m_data.get();
        }

        T& operator*() {
            this->ensure_unique();
            return *m_data.get();
        }

        const T* operator->() const {
            this->ensure_initialized();
            return m_data.get();
        }

        T* operator->() {
            this->ensure_unique();
            return m_data.get();
        }

    private:
        void ensure_initialized() const {
            if(!m_data) {
                m_data.reset(new T);
            }
        }

        void ensure_unique() {
            this->ensure_initialized();
            if(!m_data.unique()) {
                m_data.reset(new T(*m_data));
            }
        }

        mutable std::shared_ptr<T> m_data;
    };

    template <class T, class... Args>
    copy_on_write<T> make_cow(Args&&... args) {
        return copy_on_write<T>(std::forward<Args>(args)...);
    };
}