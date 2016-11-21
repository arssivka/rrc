/**
 *  @autor arssivka
 *  @date 10/31/16
 */

#pragma once


#include <memory>
#include "AbstractQueueAdapter.h"

namespace rrc {
    template <class T>
    class RingQueueAdapter : public AbstractQueueAdapter<T> {
    public:
        RingQueueAdapter(size_t size)
                : mArray(new T[size]), mTotalSize(size), mSize(0), mHead(0), mTail(0) { }

        virtual void enqueue(const T& value) override {
            this->shift();
            mArray[mTail] = value;
            mTail = (mTail + 1) % mTotalSize;
        }


        virtual void enqueue(T&& value) override {
            this->shift();
            mArray[mTail] = std::move(value);
            mTail = (mTail + 1) % mTotalSize;
        }

        virtual bool tryDequeue(T& value) override {
            if (mSize == 0) {
                return false;
            }
            value = (std::is_move_assignable<T>::value)
                    ? std::move(mArray[mHead])
                    : mArray[mHead];
            mHead = (mHead + 1) % mTotalSize;
            mSize -= 1;
            return true;
        }


    private:
        void shift() {
            if (mSize < mTotalSize) {
                mTotalSize += 1;
            } else {
                mHead = (mTail + 1) % mTotalSize;
            }
        }

    private:
        std::unique_ptr<T> mArray;
        size_t mTotalSize;
        size_t mSize;
        size_t mHead;
        size_t mTail;
    };
}