/**
 *  @autor arssivka
 *  @date 8/24/16
 */

#pragma once


#include <unordered_map>
#include <set>
#include <memory>
#include "Topic.h"

namespace rrc {
    /**
     * @brief Class that contains all the topics and grants access to them.
     */
    template <class TopicName>
    class TopicHolder {
    public:

        /**
         * @brief Constructor of billboard. Sets the default max load factor 0.8
         */
        TopicHolder() {
            // TODO Check it!
            mTopicHash.max_load_factor(0.8);
        }

        /**
         * @brief Creates topic
         * @param topicName Name of the topic
         */
        void createTopic(const TopicName& topicName) {
            auto exist = mTopicHash.find(topicName) != mTopicHash.end();
            if (!exist) {
                mTopicHash.insert({topicName, std::make_shared<Topic>()});
            }
        }

        /**
         * @brief Returns topic for the specified name
         * @param topicName Name of the needed topic
         * @return Topic if found otherwise nullptr
         */
        std::shared_ptr<Topic> getTopic(const TopicName& topicName) {
            auto found = mTopicHash.find(topicName);
            if (found != mTopicHash.end()) {
                return found->second;
            } else {
                return nullptr;
            }
        }

        /**
         * @brief Removes topic for the specified name
         * @param topicName Name of the topic
         */
        void removeTopic(const TopicName& topicName) {
            mTopicHash.erase(topicName);
        }

        /**
         * @brief Returns set of the keys of registered topics
         * @return Vector of the topics's keys
         */
        std::vector<TopicName> getTopicNames() const {
            std::vector<TopicName> names;
            names.reserve(mTopicHash.size());
            for (auto&& topic : mTopicHash) {
                names.push_back(topic.first);
            }
            return std::move(names);
        }


    private:
        std::unordered_map<TopicName, std::shared_ptr<Topic>> mTopicHash;
    };
}


