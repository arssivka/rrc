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

#include <rrc/service_holder.h>


rrc::service_holder::service_holder() {
    m_service_hash.max_load_factor(0.8);
}


void rrc::service_holder::add_service(const std::string& key,
                                      service_callback callback,
                                      const result_callback& result) {
    if (callback && m_service_hash.find(key) == m_service_hash.end()) {
        m_service_hash.emplace(key, std::move(callback));
        if (result) result(RESULT_CODE_SUCCESS);
        m_key_listener.notify(RESULT_CODE_KEY_ADDED, key);
    } else if (result) {
        result(RESULT_CODE_FAIL);
    }
}


void rrc::service_holder::remove_service(const service_callback& callback,
                                         const result_callback& result) {
    auto it = std::find_if(m_service_hash.begin(), m_service_hash.end(),
                           [&callback](const auto& pair) {
                               return pair.second == callback;
                           });
    auto key = it->first;
    m_service_hash.erase(it);
    if (it != m_service_hash.end()) {
        m_key_listener.notify(RESULT_CODE_KEY_REMOVED, key);
        if (result) result(RESULT_CODE_SUCCESS);
    } else if (result) {
        result(RESULT_CODE_FAIL);
    }
}


void rrc::service_holder::call(const std::string& key,
                               const shared_buffer input,
                               service_result_callback listener) {
    auto it = m_service_hash.find(key);
    if (it != m_service_hash.end()) {
        auto& callback = it->second;
        shared_buffer output;
        result_code result = callback(std::move(input), output);
        listener(result, output);
    }
}


std::vector<std::string> rrc::service_holder::keys() const {
    std::vector<std::string> keys;
    keys.reserve(m_service_hash.size());
    for (auto&& keyPair : m_service_hash) {
        keys.push_back(keyPair.first);
    }
    return keys;
}

void rrc::service_holder::add_key_listener(rrc::key_callback callback, const rrc::result_callback& result) {
    m_key_listener.add_listener(callback, result);
}

void rrc::service_holder::remove_key_listener(const rrc::key_callback& callback, const rrc::result_callback& result) {
    m_key_listener.remove_listener(callback, result);
}
