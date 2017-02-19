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
 *  @date 11/2/16
 */

#pragma once


#include <type_traits>
#include "advertising_mechanism.h"
#include "service_mechanism.h"
#include "settings_mechanism.h"
#include "abstract_launcher.h"
#include "system_mechanism.h"

namespace rrc {
    class mechanisms_holder {
    public:
        // TODO: Docs and tests
        mechanisms_holder(int argc, char** argv, abstract_launcher& launcher,
                          queue_adapter_factory<task>& queue_adapter_factory);

        advertising_mechanism& get_advertising_mechanism();

        service_mechanism& get_service_mechanism();

        settings_mechanism& get_settings_mechanism();

        const advertising_mechanism& get_advertising_mechanism() const;

        const service_mechanism& get_service_mechanism() const;

        const settings_mechanism& get_settings_mechanism() const;

        ~mechanisms_holder();

    private:
        abstract_launcher& m_launcher;

        std::shared_ptr<abstract_task_queue_adapter> m_system_mechanism_queue;
        std::shared_ptr<abstract_task_queue_adapter> m_advertising_mechanism_queue;
        std::shared_ptr<abstract_task_queue_adapter> m_service_mechanism_queue;
        std::shared_ptr<abstract_task_queue_adapter> m_settings_mechanism_queue;

        std::unique_ptr<system_mechanism> m_system_mechanism;
        std::unique_ptr<advertising_mechanism> m_advertising_mechanism;
        std::unique_ptr<service_mechanism> m_service_mechanism;
        std::unique_ptr<settings_mechanism> m_settings_mechanism;

    };
}