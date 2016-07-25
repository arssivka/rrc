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

        TSList() {}

        void pushFront(SPtr data) {
            std::unique_ptr<NodeType> newNode = std::make_unique<NodeType>(std::move(data));
            std::lock_guard<std::mutex> lockGuard(mHead.mMutex);
            newNode->mNext = std::move(mHead.mNext);
            mHead.mNext = std::move(newNode);
        }

        template <class T1>
        void pushFront(T1&& data) {
            std::unique_ptr<NodeType> newNode = std::make_unique<NodeType>(std::forward<T1>(data));
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
            NodeType* current = &mHead;
            std::unique_lock<std::mutex> lk(mHead.mMutex);
            while(NodeType* const next = current->mNext.get()) {
                std::unique_lock<std::mutex> nextLk(next->mMutex);
                if(func(next->mData)) {
                    std::unique_ptr<NodeType> oldNext = std::move(current->mNext);
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
            NodeType* current = &mHead;
            std::unique_lock<std::mutex> lk(mHead.mMutex);
            while(NodeType* const next = current->mNext.get()) {
                std::unique_lock<std::mutex> nextLk(next->mMutex);
                lk.unlock();
                if(func(next->mData)) {
                    return next->mData;
                }
                current = next;
                lk = std::move(nextLk);
            }
            return nullptr;
        }

    private:
        struct NodeType {
            std::mutex mMutex;
            SPtr mData;
            std::unique_ptr<NodeType> mNext;

            NodeType() : mNext() {}

            NodeType(SPtr value) : mData(value) { }

            NodeType(T&& value) : mData(std::make_shared<T>(std::forward<T>(value))) { }

        };

        NodeType mHead;

    };
}


