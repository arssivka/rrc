/**
 *  @autor arssivka
 *  @date 7/19/16
 */

#pragma once

#include <mutex>
#include <memory>
#include "NonCopyable.h"

namespace rrc {
    template <class T>
    class TSList : private NonCopyable {
    public:
        typedef T Data;
        typedef std::shared_ptr<T> SPtr;
        typedef std::unique_ptr<node> UPtrNode;

        TSList() {}

        template <class T1>
        void pushFront(T1&& data) {
            UPtrNode newNode = std::make_unique(std::forward(data));
            std::lock_guard<std::mutex> lockGuard(mHead.mMutex);
            newNode->mNext = std::move(mHead.mNext);
            mHead.mNext = std::move(newNode);
        }

        void pushFront(SPtr data) {
            UPtrNode newNode = std::make_unique(std::forward(data));
            std::lock_guard<std::mutex> lockGuard(mHead.mMutex);
            newNode->mNext = std::move(mHead.mNext);
            mHead.mNext = std::move(newNode);
        }

        SPtr popFront() {
            std::lock_guard<std::mutex> lockGuard(mHead.mMutex);
            SPtr retData = std::move(mHead.mNext->mData);
            mHead.mNext = std::move(mHead.mNext->mNext);
            return retData;
        }

        template <class Func>
        void removeIf(Func&& func) {
            node* current = &mHead;
            Func p = std::forward(func);
            std::unique_lock<std::mutex> lk(mHead.mMutex);
            while(node* const next = current->mNext.get()) {
                std::unique_lock<std::mutex> nextLk(next->mMutex);
                if(p(*next->mData)) {
                    UPtrNode oldNext = std::move(current->mNext);
                    current->mNext=std::move(next->mNext);
                    nextLk.unlock();
                }
                else {
                    lk.unlock();
                    current = next;
                    lk = std::move(nextLk);
                }
            }
        }

        template <class Func>
        SPtr applyWhile(Func&& func) {
            node* current = &mHead;
            Func p = std::forward(func);
            std::unique_lock<std::mutex> lk(mHead.mMutex);
            while(node* const next = current->mNext.get()) {
                std::unique_lock<std::mutex> nextLk(next->mMutex);
                lk.unlock();
                if(p(*next->mData)) {
                    return next->mData;
                }
                current = next;
                lk = std::move(nextLk);
            }
            return nullptr;
        }

    private:

        struct node {
            std::mutex mMutex;
            SPtr mData;
            UPtrNode mNext;

            node() : mNext() {}

            node(SPtr value) : mData(value) { }

            node(T&& value) : mData(std::make_shared<T>(std::forward(value))) { }

        };

        node mHead;

    };
}


