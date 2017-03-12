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
 *  @date 2/24/17
 */
#pragma once


#include "buffer.h"
#include "core_base.h"
#include "advertising_mechanism.h"
#include "service_mechanism.h"
#include "finalizer_mechanism.h"

namespace rrc {
    namespace defines {
        typedef rrc::lockfree_task_queue queue_type;
        typedef std::string key_type;
        typedef rrc::buffer<uint8_t> message_type;
    };

    class core
            : public core_base,
              public advertising_mechanism<defines::queue_type, defines::key_type, defines::message_type>,
              public service_mechanism<defines::queue_type, defines::key_type, defines::message_type>,
              public finalizer_mechanism<defines::queue_type> {
    public:
        core(abstract_launcher& launcher, int argc, char** argv)
                : core_base(launcher, argc, argv),
                  advertising_mechanism(launcher),
                  service_mechanism(launcher),
                  finalizer_mechanism(launcher) {}
    };
}

