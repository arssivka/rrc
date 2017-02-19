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
 *  @date 7/20/16
 */

#pragma once


#include <atomic>
#include "abstract_queue_adapter.h"
#include "defines.h"

namespace rrc {
    template <class Q>
    bool exec_once(Q& queue_ptr) {
        task t;
        if (!queue_ptr->try_dequeue(t)) return false;
        t();
        return true;
    }

    template <class Q>
    void exec_all(Q& queue_ptr) {
        task t;
        while (queue_ptr->try_dequeue(t)) {
            t();
        }
    }
}


