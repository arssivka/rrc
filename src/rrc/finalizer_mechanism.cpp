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

#include <rrc/finalizer_mechanism.h>


rrc::finalizer_mechanism::finalizer_mechanism(rrc::abstract_launcher& launcher)
        : mechanism<finalizer, 1>(launcher) {
    launcher.enqueue_finalize_task([this] {
        this->apply_changes();
        this->call(std::mem_fn(&finalizer::exec_and_clear));
    });
}


void rrc::finalizer_mechanism::add_finalize_callback(rrc::finalize_callback callback) {
    this->template enqueue_task<CHANGE_LISTENERS_PRIORITY>(
            &finalizer::add_callback,
            std::move(callback)
    );
}


void rrc::finalizer_mechanism::remove_finalize_callback(rrc::finalize_callback callback) {
    this->template enqueue_task<CHANGE_LISTENERS_PRIORITY>(
            &finalizer::remove_callback,
            std::move(callback)
    );
}
