/**
 *  @autor arssivka
 *  @date 7/18/16
 */

#pragma once


#include <memory>
#include <iostream>
namespace rrc {
    template <class T>
    class CopyOnWrite
    {
    public:
        typedef T Data;
        typedef std::shared_ptr<T> SPtr;

        CopyOnWrite(T* data = nullptr)
                : mData(data) {
        }

        CopyOnWrite(const SPtr& sptr)
                : mData(sptr) {
        }

        const T* operator->() const {
            this->ensureInitialized();
            return mData.get();
        }

        T* operator->() {
            this->ensureUnique();
            return mData.get();
        }

    private:

        void ensureInitialized() const {
            if(!mData) {
                mData.reset(new T);
            }
        }

        void ensureUnique() {
            this->ensureInitialized();
            if(!mData.unique()) {
                mData.reset(new T(*mData));
            }
        }

        mutable SPtr mData;
    };
}