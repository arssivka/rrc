/**
 *  @autor arssivka
 *  @date 11/5/16
 */

#pragma once


#include <chrono>

namespace rrc {
    class Rate {
    public:
        Rate(std::chrono::milliseconds ms);

        const std::chrono::milliseconds& getDuration() const;

        void setDuration(const std::chrono::milliseconds& duration);

        bool iterate();

        void resetControlPoint();

    private:
        std::chrono::milliseconds mDuration;
        std::chrono::steady_clock::time_point mControlPoint;
    };
}


