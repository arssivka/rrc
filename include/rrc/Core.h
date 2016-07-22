/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#pragma once


#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <future>
#include <stdlib.h>
#include "Settings.h"
#include "MessageListener.h"
#include "MessageSender.h"
#include "TSLookUp.h"
#include "TopicConnector.h"
#include "ServiceConnector.h"
#include "TSQueue.h"
#include "TaskQueue.h"
#include "AtomicWithNotifications.h"

namespace rrc {
    class Core {
    public:
        typedef std::string Key;

        Core(size_t threadsNum, int argc, char** argv);

        ~Core();

        int run();

        static Core* instance();

        static constexpr std::string getVersion();

        std::vector<std::string>& getArs() const;

        Settings* getSettings();

        bool addTopicListener(const Key& topic, MessageListener::SPtr listener);

        bool detachTopicListener(const Key& topic, const MessageListener::SPtr listener);

        bool addTopicSender(const Key& topic, MessageSender::SPtr sender);

        bool detachTopicSender(const Key& topic, const MessageSender::SPtr sender);

        bool setServiceStuff(const Key& service, MessageStuff::SPtr stuff);

        bool detachServiceStuff(const Key& service, const MessageStuff::SPtr stuff);

        bool addClientStuff(const Key& service, MessageStuff::SPtr stuff);

        bool detachClientStuff(const Key& service, const MessageStuff::SPtr stuff);

        template <class Func>
        bool setEntryForID(const ID& id, Func&& func) {
            auto env = mEnvironments.get(id);
            auto queue = env->getTaskQueue();
            auto dur = env->getCallDuration();
            env = std::make_shared<ModuleEnvironment>(std::forward<Func>(func));
            env->setTaskQueue(queue);
            env->setCallDuration(dur);
            mEnvironments.set(id, std::move(env));
            return true;
        }

        bool setCallDurationForID(const ID& id, std::chrono::duration duration);

        bool detachEntryForID(const ID& id);

        TaskQueue::SPtr getTaskQueue(const ID& id) const;

        bool isFinished() const;

        void finish();

    private:
        void waitForStart();

    private:
        typedef TSLookUp<Key, TopicConnector> TopicsContainer;
        typedef TSLookUp<Key, ServiceConnector> ServicesContainer;
        typedef TSLookUp<ID, ModuleEnvironment> ModuleEnvironmentsContainer;

        class ModuleEnvironment {
        public:
            static constexpr std::chrono::duration getDefaultDuration();

            ModuleEnvironment() = default;

            template <class Func>
            ModuleEnvironment(Func&& func)
                    : mFinished(ATOMIC_FLAG_INIT),
                      mCallDuration(this->getDefaultDuration()),
                      mTaskQueue(std::make_shared<TaskQueue>()) {
                mFinished.test_and_set(std::memory_order_release);
                std::packaged_task<void()> task([this]() {
                    Func callback = std::forward<Func>(func);
                    Core *core = Core::instance();
                    core->waitForStart();
                    while (mFinished.test_and_set(std::memory_order_acquire) && !core->isFinished()) {
                        auto start = rrc::Clock::now();
                        callback();
                        auto end = rrc::Clock::now();
                        rrc::Clock::duration duration = end - start;
                        if (duration < mCallDuration) {
                            std::this_thread::sleep_for(mCallDuration.load(std::memory_order_acquire) - duration);
                        }
                    }
                });
                mExceptionHolder = task.get_future();
                mWorker = std::thread(std::move(task));
            }
            
            void setCallDuration(std::chrono::duration duration);

            rrc::Clock::duration getCallDuration() const;
            
            TaskQueue::SPtr getTaskQueue() const;

            void setTaskQueue(TaskQueue::SPtr mTaskQueue);

            ~ModuleEnvironment();

        private:
            std::thread mWorker;
            TaskQueue::SPtr mTaskQueue;
            std::atomic<rrc::Clock::duration> mCallDuration;
            std::atomic_flag mFinished;
            std::future<void> mExceptionHolder;
        };

    private:
        static Core* sInstance;
        std::vector<std::string> mArgs;
        Settings mSettings;
        TopicsContainer mTopics;
        ServicesContainer mServices;
        ModuleEnvironmentsContainer mEnvironments;

        AtomicWithNotifications<bool> mStartedFlag;
        AtomicWithNotifications<bool> mFinishedFlag;
    };
}


