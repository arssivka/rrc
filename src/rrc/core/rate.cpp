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
 *  @date 11/5/16
 */

#include <rrc/core/rate.h>


rrc::rate::rate(std::chrono::milliseconds ms)
        : mDuration(ms) { }


const std::chrono::milliseconds& rrc::rate::duration() const {
    return mDuration;
}


void rrc::rate::set_duration(const std::chrono::milliseconds& duration) {
    mDuration = duration;
}


bool rrc::rate::iterate() {
    auto now = std::chrono::steady_clock::now();
    if (now > mControlPoint + mDuration) {
        mControlPoint = now;
        return true;
    }
    return false;
}


void rrc::rate::reset() {
    mControlPoint = std::chrono::steady_clock::time_point();
}
