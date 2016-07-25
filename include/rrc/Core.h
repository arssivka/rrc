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

        static std::string getVersion();

        const std::vector<std::string>& getArs() const;

        Settings* getSettings();

        bool addTopicListener(const Key& topic, MessageListener::SPtr listener);

        bool detachTopicListener(const Key& topic, const MessageListener::SPtr listener);

        bool addTopicSender(const Key& topic, MessageSender::SPtr sender);

        bool detachTopicSender(const Key& topic, const MessageSender::SPtr sender);

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

        bool setCallDurationForID(const ID& id, Duration duration);

        bool detachEntryForID(const ID& id);

        TaskQueue::SPtr getTaskQueue(const ID& id) const;

        bool isFinished() const;

        void finish();

    private:
        void waitForStart();

    private:
        class ModuleEnvironment {
        public:
            static Duration getDefaultDuration();

            ModuleEnvironment() = default;

            template <class Func>
            ModuleEnvironment(Func&& func)
                    : mTaskQueue(std::make_shared<TaskQueue>()),
                      mCallDuration(this->getDefaultDuration()),
                      mFinished(ATOMIC_FLAG_INIT) {
                mFinished.test_and_set(std::memory_order_release);
                std::packaged_task<void()> task([&, this]() {
                    Func callback = std::forward<Func>(func);
                    Core *core = Core::instance();
                    core->waitForStart();
                    while (mFinished.test_and_set(std::memory_order_acquire) && !core->isFinished()) {
                        TimePoint start = rrc::Clock::now();
                        callback();
                        TimePoint end = rrc::Clock::now();
                        Duration duration = end - start;
                        if (duration < mCallDuration.load(std::memory_order_release)) {
                            std::this_thread::sleep_for(mCallDuration.load(std::memory_order_acquire) - duration);
                        }
                    }
                });
                mExceptionHolder = task.get_future();
                mWorker = std::thread(std::move(task));
            }
            
            void setCallDuration(Duration duration);

            Duration getCallDuration() const;
            
            TaskQueue::SPtr getTaskQueue() const;

            void setTaskQueue(TaskQueue::SPtr mTaskQueue);

            ~ModuleEnvironment();

        private:
            std::thread mWorker;
            TaskQueue::SPtr mTaskQueue;
            std::atomic<rrc::Duration> mCallDuration;
            std::atomic_flag mFinished;
            std::future<void> mExceptionHolder;
        };

        typedef TSLookUp<Key, TopicConnector> TopicsContainer;
        typedef TSLookUp<ID, ModuleEnvironment> ModuleEnvironmentsContainer;

    private:
        static Core* sInstance;
        std::vector<std::string> mArgs;
        Settings mSettings;
        TopicsContainer mTopics;
        ModuleEnvironmentsContainer mEnvironments;

        AtomicWithNotifications<bool> mStartedFlag;
        AtomicWithNotifications<bool> mFinishedFlag;
    };
}


