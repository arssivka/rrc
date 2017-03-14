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
 *  @date 3/9/17
 */
#pragma once

#include <cstddef>
#include <utility>

namespace rrc {
    template <class T, size_t N>
    class elem_less {
    public:
        typedef T first_argument_type;
        typedef T second_argument_type;
        typedef bool result_type;

        bool operator() (const T& x, const T& y) const {return std::get<N>(x) < std::get<N>(y);}
    };
}