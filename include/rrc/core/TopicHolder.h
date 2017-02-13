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
         * @brief Register message listener
         * @param topicName Name of the topic
         * @param listener Pointer to listener to register
         */
        void addListener(const TopicName& name, std::shared_ptr<TaskHub> listener) {
            auto found = mTopicHash.find(name);
            if (found == mTopicHash.end()) {
                found = mTopicHash.emplace(name, Topic()).first;
            }
            auto& topic = found->second;
            topic.addListener(std::move(listener));
        }

        // TODO: Docs
        void removeListener(const TopicName& name, std::weak_ptr<TaskHub> listener) {
            auto iterator = mTopicHash.find(name);
            if (iterator != mTopicHash.end()) {
                auto& topic = iterator->second;
                topic.removeListener(listener);
            }
        }

        /**
         * @brief Sends the message
         * @param topicName Name of the topic
         * @param message Pointer to message that needs to be sent
         */
        void sendMessage(const TopicName& name, std::shared_ptr<Buffer> message) {
            auto found = mTopicHash.find(name);
            if (found != mTopicHash.end()) {
                auto& topic = found->second;
                topic.sendMessage(std::move(message));
            }
        }

        /**
         * @brief Returns set of the keys of registered topics
         * @return Vector of the topics's keys
         */
        std::vector<TopicName> getNames() const {
            std::vector<TopicName> names;
            names.reserve(mTopicHash.size());
            for (auto&& topic : mTopicHash) {
                names.push_back(topic.first);
            }
            return std::move(names);
        }


    private:
        std::unordered_map<TopicName, Topic> mTopicHash;
    };
}


