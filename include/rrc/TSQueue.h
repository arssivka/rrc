/**
 *  @autor arssivka
 *  @date 7/18/16
 */

#pragma once


#include <mutex>
#include <queue>
#include <memory>
#include "NonCopyable.h"

namespace rrc {
    template<class T>
    class TSQueue : private NonCopyable {
    public:
        typedef T Data;
        typedef std::shared_ptr<T> SPtr;

        TSQueue() {}

        template <class Type>
        void push(Type&& data) {
            SPtr ptr = std::make_shared<T>(std::forward<Type>(data));
            std::lock_guard<std::mutex> lock(mMutex);
            mQueue.push(std::move(ptr));
        }

        void push(SPtr data) {
            std::lock_guard<std::mutex> lock(mMutex);
            mQueue.push(std::move(data));
        }

        SPtr pop() {
            SPtr res = nullptr;
            {
                std::lock_guard<std::mutex> lock(mMutex);
                if (!mQueue.empty()) {
                    res = std::move(mQueue.front());
                    mQueue.pop();
                }
            }
            return res;
        }

        bool pop(T& data) {
            bool stat = false;
            std::lock_guard<std::mutex> lock(mMutex);
            if (!mQueue.empty()) {
                stat = true;
                data = std::move(*mQueue.front());
                mQueue.pop();
            }
            return stat;
        }

    private:
        mutable std::mutex mMutex;
        std::queue<SPtr> mQueue;
    };
}


