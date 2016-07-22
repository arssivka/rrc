/**
 *  @autor arssivka
 *  @date 7/8/16
 */

#include "include/rrc/Core.h"
#include "VersionDefines.h"


std::string static constexpr rrc::Core::getVersion() {
    return std::string(RRC_VERSION);
}


std::vector<std::string>& rrc::Core::getArs() const {
    return mArgs;
}


Settings* rrc::Core::getSettings() {
    return &mSettings;
}

Core* rrc::Core::instance() {
    return sInstance;
}


bool rrc::Core::addTopicListener(const Key& topic, MessageListener::SPtr listener) {
    auto connector = TopicConnector(listener->getDescriptor());
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
    auto connector = TopicConnector(sender->getDescriptor());
    TopicsContainer::SPtr tptr = mTopics.get(topic);
    return tptr->addSender(sender);
}


bool rrc::Core::detachTopicSender(const Key& topic, const MessageSender::SPtr sender) {
    TopicsContainer::SPtr tptr = mTopics.get(topic);
    return tptr->detachSender(sender);
}


bool rrc::Core::setServiceStuff(const Key& service, MessageStuff::SPtr stuff) {
    ServicesContainer::SPtr sptr = mServices.get(service);
    return sptr->setServiceStuff(stuff);
}


bool rrc::Core::detachServiceStuff(const Key& service, const MessageStuff::SPtr stuff) {
    ServicesContainer::SPtr sptr = mServices.get(service);
    if (sptr != nullptr) {
        return sptr->detachServiceStuff(stuff);
    }
    return false;
}


bool rrc::Core::addClientStuff(const Key& service, MessageStuff::SPtr stuff) {
    auto connector = ServiceConnector(stuff->getListenerDescriptor(),
                                      stuff->getListenerDescriptor());
    ServicesContainer::SPtr sptr = mServices.get(service);
    return sptr->addClientStuff(stuff);
}


bool rrc::Core::detachClientStuff(const Key& service, const MessageStuff::SPtr stuff) {
    ServicesContainer::SPtr sptr = mServices.get(service);
    if (sptr != nullptr) {
        return sptr->detachClientStuff(stuff);
    }
    return false;
}

bool rrc::Core::setCallDurationForID(const rrc::ID &id, std::chrono::duration duration) {
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

constexpr std::chrono::duration rrc::Core::ModuleEnvironment::getDefaultDuration() {
    return std::chrono::milliseconds(10);
}

void rrc::Core::ModuleEnvironment::setCallDuration(std::chrono::duration duration) {
    mCallDuration.store(duration, std::memory_order_release);
}

rrc::Clock::duration rrc::Core::ModuleEnvironment::getCallDuration() const {
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
