/**
 *  @autor arssivka
 *  @date 11/5/16
 */

#include "include/rrc/core/Rate.h"


rrc::Rate::Rate(std::chrono::milliseconds ms)
        : mDuration(ms) { }


const std::chrono::milliseconds& rrc::Rate::getDuration() const {
    return mDuration;
}


void rrc::Rate::setDuration(const std::chrono::milliseconds& duration) {
    mDuration = duration;
}


bool rrc::Rate::iterate() {
    auto now = std::chrono::steady_clock::now();
    if (now > mControlPoint + mDuration) {
        mControlPoint = now;
        return true;
    }
    return false;
}


void rrc::Rate::resetControlPoint() {
    mControlPoint = std::chrono::steady_clock::time_point();
}
