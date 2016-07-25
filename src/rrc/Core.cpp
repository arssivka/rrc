/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#include "include/rrc/Core.h"
#include "VersionDefines.h"


std::string rrc::Core::getVersion() {
    return std::string(RRC_VERSION);
}


const std::vector<std::string>& rrc::Core::getArs() const {
    return mArgs;
}


rrc::Settings* rrc::Core::getSettings() {
    return &mSettings;
}

rrc::Core* rrc::Core::instance() {
    return sInstance;
}


bool rrc::Core::addTopicListener(const Key& topic, MessageListener::SPtr listener) {
    TopicsContainer::SPtr tptr = mTopics.get(topic);
    return tptr->addListener(listener);
}


bool rrc::Core::detachTopicListener(const Key& topic, const MessageListener::SPtr listener) {
    TopicsContainer::SPtr tptr = mTopics.get(topic);
    if (tptr != nullptr) {
        return tptr->detachListener(listener);
    }
    return false;
}


bool rrc::Core::addTopicSender(const Key& topic, MessageSender::SPtr sender) {
    TopicsContainer::SPtr tptr = mTopics.get(topic);
    return tptr->addSender(sender);
}


bool rrc::Core::detachTopicSender(const Key& topic, const MessageSender::SPtr sender) {
    TopicsContainer::SPtr tptr = mTopics.get(topic);
    return tptr->detachSender(sender);
}


bool rrc::Core::setCallDurationForID(const rrc::ID &id, Duration duration) {
    auto env = mEnvironments.get(id);
    env->setCallDuration(duration);
    return true;
}

bool rrc::Core::detachEntryForID(const rrc::ID &id) {
    auto env = mEnvironments.detach(id);
    auto queue = env->getTaskQueue();
    queue->disable();
    return true;
}

rrc::TaskQueue::SPtr rrc::Core::getTaskQueue(const rrc::ID &id) const {
    auto env = mEnvironments.get(id);
    return env->getTaskQueue();
}

int rrc::Core::run() {
    mStartedFlag.store(true, std::memory_order_release);
    mFinishedFlag.wait([](const AtomicWithNotifications<bool>::Atomic& data) -> bool {
        return data.load(std::memory_order_acquire);
    });
    return EXIT_SUCCESS;
}

rrc::Core::~Core() {
    sInstance = nullptr;
}

rrc::Core::Core(size_t threadsNum, int argc, char** argv)
        : mArgs(&argv[0], &argv[argc]), mStartedFlag(false), mFinishedFlag(false) { }

bool rrc::Core::isFinished() const {
    return mFinishedFlag.load(std::memory_order_acquire);
}

void rrc::Core::finish() {
    mFinishedFlag.store(true, std::memory_order_release);
}

void rrc::Core::waitForStart() {
    mStartedFlag.wait([](const AtomicWithNotifications<bool>::Atomic& data) -> bool {
        return data.load(std::memory_order_acquire);
    });
}

rrc::Duration rrc::Core::ModuleEnvironment::getDefaultDuration() {
    return std::chrono::milliseconds(10);
}

void rrc::Core::ModuleEnvironment::setCallDuration(rrc::Duration duration) {
    mCallDuration.store(duration, std::memory_order_release);
}

rrc::Duration rrc::Core::ModuleEnvironment::getCallDuration() const {
    return mCallDuration.load(std::memory_order_acquire);
}

rrc::TaskQueue::SPtr rrc::Core::ModuleEnvironment::getTaskQueue() const {
    return mTaskQueue;
}

void rrc::Core::ModuleEnvironment::setTaskQueue(rrc::TaskQueue::SPtr mTaskQueue) {
    ModuleEnvironment::mTaskQueue = std::move(mTaskQueue);
}

rrc::Core::ModuleEnvironment::~ModuleEnvironment() {
    if (mWorker.joinable()) {
        mFinished.clear(std::memory_order_release);
        mExceptionHolder.get();
        mWorker.join();
    }
}
