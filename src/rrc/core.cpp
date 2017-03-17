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

#include <rrc/core.h>

rrc::core::core(rrc::abstract_launcher& launcher, int argc, char** argv)
        : core_base(launcher, argc, argv),
          m_topic_mechanism(launcher),
          m_service_mechanism(launcher),
          m_finalizer_mechanism(launcher) {}

const rrc::topic_mechanism& rrc::core::topics() const {
    return m_topic_mechanism;
}

const rrc::service_mechanism& rrc::core::services() const {
    return m_service_mechanism;
}

const rrc::finalizer_mechanism& rrc::core::finalizers() const {
    return m_finalizer_mechanism;
}

rrc::topic_mechanism& rrc::core::topics() {
    return m_topic_mechanism;
}

rrc::service_mechanism& rrc::core::services() {
    return m_service_mechanism;
}

rrc::finalizer_mechanism& rrc::core::finalizers() {
    return m_finalizer_mechanism;
}
