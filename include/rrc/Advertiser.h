/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include "ID.h"
#include "Message.h"
#include "MessageSender.h"
#include "Core.h"

namespace rrc {
    template <typename MessageType>
    class Advertiser {
    public:
        Advertiser(const ID& id, const std::string& topic) {
            mTopic = topic;
            mSender = std::make_shared<MessageSender>(id);
            this->connect();
        }

        ~Advertiser() {
            this->disconnect();
        }


        bool disconnect() {
            if (mConnected) {
                Core* core = Core::instance();
                return core->detachTopicSender(mTopic, mSender);
            }
            return false;
        }

        bool reconnect() {
            this->disconnect();
            this->connect();
        }

        bool isConnected() const {
            return mConnected;
        }

        void send(Message<MessageType> msg, bool updateTimestamp = true) {
            if (updateTimestamp) msg.setTimestamp(Clock.now());
            mSender->send(msg);
        }

    private:
        void connect() {
            Core* core = Core::instance();
            mConnected = core->addTopicSender(mTopic, mSender);
        }

    private:

        MessageSender::SPtr mSender;
        std::string mTopic;
        bool mConnected;
    };
}


