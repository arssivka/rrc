/**
 *  @autor tekatod
 *  @date 7/18/16
 */
#pragma once

#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <algorithm>
#include <vector>
#include "NonCopyable.h"

namespace rrc {
    template<typename K, typename D, typename H=std::hash<K> >
    class TSLookUp : private NonCopyable {
    public:
        typedef K Key;
        typedef D Data;
        typedef std::shared_ptr<D> Ptr;
        typedef H Hash;

        TSLookUp(
                unsigned numBuckets = 19, const Hash& hasher = Hash()) :
                mBuckets(numBuckets), mHasher(hasher) {
            for (unsigned i = 0; i < numBuckets; ++i) {
                mBuckets[i].reset(new Bucket);
            }
        }

        const Ptr get(const K& key) const {
            return this->getBucket(key).valueFor(key);
        }

        Ptr get(const K& key) {
            return this->getBucket(key).valueFor(key);
        }

        Ptr detach(const K& key) const {
            return this->getBucket(key).detachFor(key);
        }

        void set(const K& key, Ptr value) {
            this->getBucket(key).addOrUpdate(key, std::move(value));
        }

        template <class Value>
        void set(const K& key, Value&& value) {
            this->getBucket(key).addOrUpdate(key, std::make_shared<D>(std::forward<Value>(value)));
        }
        
        bool contains(const K& key) const {
            return this->getBucket(key).contains(key);
        }

        bool remove(const K& key) {
            return this->getBucket(key).remove(key);
        }

    private:
        class Bucket {
        public:
            const Ptr valueFor(const K& key) const {
                std::lock_guard<std::mutex> lock(mMutex);
                const BucketIterator found = this->findEntryFor(key);
                if (found == mData.end()) {
                    mData.emplace_back(key, std::make_shared<D>());
                    return mData.back().second;
                } else {
                    return found->second;
                }
            }

            Ptr valueFor(const K& key) {
                std::lock_guard<std::mutex> lock(mMutex);
                const BucketIterator found = this->findEntryFor(key);
                if (found == mData.end()) {
                    // TODO There may be a better solution
                    mData.emplace_back(key, std::make_shared<D>());
                    return mData.back().second;
                } else {
                    return found->second;
                }
            }
            
            bool contains(const Key& key) const {
                return this->findEntryFor(key) != mData.end();
            }

            Ptr detachFor(const K& key) {
                std::lock_guard<std::mutex> lock(mMutex);
                BucketIterator const found = this->findEntryFor(key);
                Ptr res = nullptr;
                if (found != mData.end()) {
                    res = std::move(found->second);
                }
                mData.erase(found);
                return res;
            }

            void addOrUpdate(const K& key, Ptr value) {
                std::lock_guard<std::mutex> lock(mMutex);
                const BucketIterator found = this->findEntryFor(key);
                if (found == mData.end()) {
                    mData.emplace_back(key, std::move(value));
                } else {
                    found->second = std::move(value);
                }
            }

            bool remove(K const &key) {
                std::unique_lock<std::mutex> lock(mMutex);
                const BucketIterator found = this->findEntryFor(key);
                if (found != mData.end()) {
                    mData.erase(found);
                    return true;
                }
                return false;
            }

        private:
            typedef std::pair<K, Ptr> BucketValue;
            typedef std::list<BucketValue> BucketList;
            typedef typename BucketList::iterator BucketIterator;

        private:
            BucketIterator findEntryFor(const K& key) const {
                return std::find_if(mData.begin(), mData.end(),
                                    [&](const BucketValue& item) {
                                        return item.first == key;
                                    });
            }


        private:
            mutable BucketList mData;
            mutable std::mutex mMutex;
        };

        Bucket& getBucket(const K& key) const {
            std::size_t const bucket_index = mHasher(key) % mBuckets.size();
            return *mBuckets[bucket_index];
        }

        std::vector<std::unique_ptr<Bucket>> mBuckets;
        Hash mHasher;
    };
}