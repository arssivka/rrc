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


#include "core_base.h"
#include "topic_mechanism.h"
#include "service_mechanism.h"

namespace rrc {
    class core : public core_base {
    public:
        core(abstract_launcher& launcher, int argc, char** argv);

        const topic_mechanism& topics() const;

        const service_mechanism& services() const;

        topic_mechanism& topics();

        service_mechanism& services();

    private:
        topic_mechanism m_topic_mechanism;
        service_mechanism m_service_mechanism;
    };
}

