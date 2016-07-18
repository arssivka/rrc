/**
 *  @autor arssivka
 *  @date 7/11/16
 */

#pragma once


#include <memory>
#include <chrono>
#include "Clock.h"
#include "CopyOnWrite.h"

namespace rrc {
    template <class T>
    class Message {
    public:
        Message() = default;

        template <class D>
        Message(D&& data) {
            mData->second = std::forward<D>(data);
        }

        template <class D>
        Message(TimePoint time, D&& data) {
            mData->second = std::forward<D>(data);
            mData->first = time;
        }

        const T& getData() const {
            return mData->second;
        }

        const TimePoint& getTimestamp() const {
            return mData->first;
        }

        template <class D>
        void setData(D&& data) {
            mData->second = std::forward<D>(data);
        }

        void setTimestamp(TimePoint time) {
            mData->first = time;
        }

    private:
        typedef std::pair<TimePoint, T> Bucket;

        CopyOnWrite<Bucket> mData;
    };
}


