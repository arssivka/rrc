/**
 *  @autor arssivka
 *  @date 7/18/16
 */

#pragma once


#include <memory>
#include <iostream>
namespace rrc {
    /**
     * @brief Class that makes his child classes to be copied only when modified.
     */
    template <class T>
    class CopyOnWrite
    {
    public:
        typedef T Data;
        typedef std::shared_ptr<T> Ptr;

        template <class... Args>
        static CopyOnWrite create(Args... args) {
            Data data = std::make_shared<Data>(std::forward<Args>(args)...);
            return CopyOnWrite(std::move(data));
        }

        CopyOnWrite(T* data = nullptr)
                : mData(data) {
        }

        CopyOnWrite(const Ptr& sptr)
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

        mutable Ptr mData;
    };
}