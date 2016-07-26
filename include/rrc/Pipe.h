/**
 *  @autor arssivka
 *  @date 7/13/16
 */

#pragma once


#include <functional>
#include "ID.h"
#include "Message.h"
#include "NonCopyable.h"

namespace {
    namespace pb = google::protobuf;
}

namespace rrc {
    template <class T>
    class Pipe : private NonCopyable {
    public:
        typedef T Type;

        Pipe(const ID& id, const std::string& topic) : mId(id), mTopic(topic), mConnected(false) { }

        template <class Func>
        Pipe(const ID& id, const std::string& topic, Func&& callback)
                : mId(id), mTopic(topic), mConnected(false) {
            this->setCallback(std::forward<Func>(callback));
        }

        bool isConnected() const {
            return mConnected;
        }

        bool disconnect() const {
            if (mConnected) {
                Core* core = Core::instance();
                return core->detachTopicListener(mTopic, mListener);
            }
            return false;
        }

        bool reconnect() {
            this->disconnect();
            this->connect();
            return this->isConnected();
        }

        template <class Func>
        void setCallback(Func&& callback) {
            this->disconnect();
            this->createListener(std::forward<Func>(callback));
            this->connect();
        }

    private:
        template <class Func>
        void createListener(Func&& callback) {
            mListener = std::make_shared<Listener>(std::forward<Func>(callback));
            mListener->setId(this->);
        }

        void connect() {
            Core* core = Core::instance();
            mConnected = core->addTopicListener(mTopic, mListener);
        }

    private:
        class Listener : public MessageListener {
        public:
            typedef std::shared_ptr<Listener> SPtr;

            template <class Func>
            Listener(const ID& id, Func&& func) : Message(id) {
                Core* core = Core::instance();
                mTaskQueue = core->getTaskQueue(id);
                mCallback = std::forward<Func>(func);
                // TODO Get descriptor
            }


            virtual void onMessage(const ID& id, Message<pb::Message> msg, bool directCall) override {
                if (directCall && this->isDirectCallEnabled() && id == this->getId()) {
                    mCallback(msg);
                } else {
                    mTaskQueue->enqueue(mCallback, msg);
                }
            }

        private:
            TaskQueue::SPtr mTaskQueue;
            std::function<void(rrc::Message<T>)> mCallback;
        };

        ID mId;
        std::string mTopic;
        bool mConnected;
        Listener::SPtr mListener;
    };
}


