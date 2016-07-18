/**
 *  @autor arssivka
 *  @date 7/13/16
 */

#pragma once


#include <memory>
#include <atomic>
#include "Message.h"

namespace rrc {
    template <class T>
    class Response {
    public:
        typedef T Type;

        Response() : mDataSetted(ATOMIC_FLAG_INIT), mData(nullptr) { }

        Message<T> get() const noexcept {
            return mData;
        }

        bool set(Message<T> data) noexcept {
            // TODO Check memory order
            if (mDataSetted.test_and_set(std::memory_order_acq_rel)) {
                mData = data;
                return  true;
            }
            return false;
        }

    private:
        std::atomic_flag mDataSetted;
        Message<T> mData;
    };
}


