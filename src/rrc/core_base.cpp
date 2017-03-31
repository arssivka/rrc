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

#include <rrc/core_base.h>


rrc::core_base::core_base(rrc::abstract_launcher& launcher, int argc, char** argv)
        : m_launcher(launcher) {
    m_args.assign(argv + 1, argv + argc);
}


const std::vector<std::string>& rrc::core_base::args() const noexcept {
    return m_args;
}


void rrc::core_base::stop() {
    m_launcher.stop();
}
