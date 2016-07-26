/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include "Core.h"
#include "ID.h"
#include "Message.h"
#include "NonCopyable.h"
#include "MessageListener.h"
#include "TaskQueue.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    template <typename T>
    class Subscriber : private NonCopyable {
    public:
        typedef T Type;

        Subscriber(const ID& id, const std::string& topic, size_t queueSize) {
            mConnected = false;
            mTopic = topic;
            this->connect();
        }

        ~Subscriber() {
            this->disconnect();
        }

        bool disconnect() {
            if (mConnected) {
                Core* core = Core::instance();
                return core->detachTopicListener(mTopic, mListener);
            }
            return false;
        }

        bool isConnected() const {
            return mConnected;
        }

        bool reconnect() {
            this->disconnect();
            this->connect();
        }

        Message<T> pop() {
            return mListener->pop();
        }

    private:
        void connect() {
            Core* core = Core::instance();
            mConnected = core->addTopicListener(mTopic, mListener);
        }

    private:
        class Listener : public MessageListener {
        public:
            typedef std::shared_ptr<Listener> SPtr;

            Listener() {
                // TODO Get descriptor
                //this->setDescriptor();
            }

            virtual void onMessage(const ID& id, Message<pb::Message> msg, bool directCall) override {
                mMessageQueue.push(msg);
            }

            Message<T> pop() {
                Message<T> res;
                return mMessageQueue.pop(res) ? res : Message<T>();
            }

        private:
            TSQueue<Message<T>> mMessageQueue;
        };

        Listener::SPtr mListener;
        bool mConnected;
        std::string mTopic;
    };
}
