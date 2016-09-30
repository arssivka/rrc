/**
 *  @autor arssivka
 *  @date 8/24/16
 */

#pragma once


#include <unordered_map>
#include <set>
#include "QueueMessageListener.h"
#include "Topic.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    /**
     * @brief Class that contains all the topics and grants access to them.
     */
    template <class Key>
    class Billboard {
    public:

        /**
         * @brief Constructor of billboard. Sets the default max load factor 0.8
         */
        Billboard() {
            // TODO Check it!
            mTopicHash.max_load_factor(0.8);
        }

        /**
         * @brief Creates topic
         * @param key Key of the topic
         * @param tid Id of the type for the topic
         */
        void createTopic(const Key& key) {
            mTopicHash.insert({key, std::make_shared<Topic>()});
        }

        /**
         * @brief Returns topic for the specified key
         * @param key Key of the needed topic
         * @return Topic if found otherwise nullptr
         */
        TopicPtr getTopic(const Key& key) {
            auto found = mTopicHash.find(key);
            if (found != mTopicHash.end()) {
                return found->second;
            } else {
                return nullptr;
            }
        }

        /**
         * @brief Removes topic for the specified key
         * @param key Key of the topic
         */
        void removeTopic(const Key& key) {
            mTopicHash.erase(key);
        }

        /**
         * @brief Returns set of the keys of registered topics
         * @return Set of the topics's keys
         */
        std::vector<Key> getKeys() const {
            std::vector<Key> keys;
            keys.reserve(mTopicHash.size());
            for (auto&& topic : mTopicHash) {
                keys.push_back(topic.first);
            }
            return std::move(keys);
        }


    private:
        std::unordered_map<Key, TopicPtr> mTopicHash;
    };
}


