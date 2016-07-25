/**
 *  @autor arssivka
 *  @date 7/18/16
 */

#pragma once


#include <chrono>

namespace rrc {
    typedef std::chrono::steady_clock Clock;
    typedef std::chrono::steady_clock::time_point TimePoint;
    typedef std::chrono::steady_clock::duration Duration;
}