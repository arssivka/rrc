/**
 *  @autor arssivka
 *  @date 7/18/16
 */

#pragma once


#include <memory>

namespace rrc {
    template <class T>
    class CopyOnWrite
    {
    public:
        typedef T Data;

        CopyOnWrite(T* data = nullptr)
                : mData(data) {
        }

        const T* operator->() const {
            return mData.get();
        }

        T* operator->() {
            if (!mData.unique())
                mData.reset(new T(*mData));
            return mData.get();
        }

    private:
        std::shared_ptr<T> mData;

    };
}