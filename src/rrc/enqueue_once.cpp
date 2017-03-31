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
 *  @date 3/31/17
 */

#include "rrc/enqueue_once.h"


rrc::enqueue_once::enqueue_once(rrc::abstract_launcher& launcher)
        : m_launcher(launcher),
          m_enqueued_flag(ATOMIC_FLAG_INIT) {}


void rrc::enqueue_once::exec() {
    m_func();
    m_enqueued_flag.clear(std::memory_order_release);
}
