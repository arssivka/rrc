/**
 *  @autor arssivka
 *  @date 8/24/16
 */

#pragma once


#include <unordered_map>
#include <set>
#include "MessageListener.h"
#include "Topic.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    template <class Key>
    class Billboard {
    public:
        Billboard() {
            // TODO Check it!
            mTopicHash.max_load_factor(0.8);
        }

        void createTopic(const Key& key, TypeId tid) {
            mTopicHash.insert({key, std::make_shared<Topic>(tid)});
        }

        TopicPtr getTopic(const Key& key) {
            auto found = mTopicHash.find(key);
            if (found != mTopicHash.end()) {
                return found->second;
            } else {
                return nullptr;
            }
        }

        void removeTopic(const Key& key) {
            mTopicHash.erase(key);
        }

        std::set<Key> getKeys() const {
            std::set<Key> mKeysSet;
            for (auto&& topic : mTopicHash) {
                mKeysSet.insert(topic.first);
            }
            return mKeysSet;
        }


    private:
        std::unordered_map<Key, TopicPtr> mTopicHash;
    };
}


