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

#include <rrc/key_listener.h>

void rrc::key_listener::add_listener(rrc::key_callback callback, const rrc::result_callback& result) {
    if (callback) {
        m_key_listeners.push_front(callback);
        if (result) result(RESULT_CODE_SUCCESS);
    } else if (result) {
        result(RESULT_CODE_FAIL);
    }
}


void rrc::key_listener::remove_listener(const rrc::key_callback& callback,
                                        const rrc::result_callback& result) {
    result_code code = RESULT_CODE_FAIL;
    m_key_listeners.remove_if([&code, &callback](const key_callback& curr) -> bool {
        if (callback == curr) {
            code = RESULT_CODE_SUCCESS;
            return true;
        }
        return false;
    });
    if (result) result(code);
}


void rrc::key_listener::notify(rrc::result_code code, const std::string& key) {
    for (auto&& callback : m_key_listeners) {
        callback(code, key);
    }
}
