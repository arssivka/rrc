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
 *  @date 3/17/17
 */
#pragma once


#include <unordered_set>
#include <dotconf.h>
#include "callback_defines.h"

namespace rrc {
    template <class T>
    class notifier {
    public:
        typedef T callback_type;

        notifier() {
            m_listeners.max_load_factor(0.8);
        }

        bool add_listener(callback_type callback, const rrc::result_callback& result) {
            result_code code = RESULT_CODE_FAIL;
            if (callback && m_listeners.find(callback) == m_listeners.end()) {
                m_listeners.emplace(callback);
                code = RESULT_CODE_SUCCESS;
            }
            if (result) result(code);
            return code == RESULT_CODE_SUCCESS;
        }

        bool remove_listener(const callback_type& callback, const rrc::result_callback& result) {
            result_code code = RESULT_CODE_FAIL;
            auto it = m_listeners.find(callback);
            if (it != m_listeners.end()) {
                m_listeners.erase(it);
                code = RESULT_CODE_SUCCESS;
            }
            if (result) result(code);
            return code == RESULT_CODE_SUCCESS;
        }

        template <class... Args>
        void notify(Args&&... args) {
            for (auto&& callback : m_listeners) {
                callback(std::forward<Args>(args)...);
            }
        }

        size_t size() const {
            return m_listeners.size();
        }

    private:
        std::unordered_set<callback_type> m_listeners;
    };
}

