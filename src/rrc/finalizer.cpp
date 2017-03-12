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
 *  @date 3/1/17
 */


#include <rrc/finalizer.h>


void rrc::finalizer::add_callback(std::shared_ptr<rrc::finalizer::callback_type> callback_ptr) {
    m_callback_list.push_front(callback_ptr);
}

void rrc::finalizer::remove_callback(std::shared_ptr<rrc::finalizer::callback_type> callback_ptr) {
    m_callback_list.remove(callback_ptr);
}

void rrc::finalizer::exec_all() {
    for (auto&& callback_ptr : m_callback_list) {
        auto& callback = *callback_ptr;
        callback();
    }
    m_callback_list.clear();
}
