///**
// *  @autor arssivka
// *  @date 9/2/16
// */
//
//#pragma once
//
//
//#include <rrc/core/QueueMessageListener.h>
//
//class DummyNode : public rrc::AbNode {
//public:
//    DummyNode(rrc::RootNodePtr rootNode, const std::string& topicName);
//
//    virtual void entry() override {
//        this->incrementCounter();
//        if (mCounter == 5) {
//            mRootNode->stop();
//        }
//    }
//
//    void incrementCounter();
//
//    void resetCounter();
//
//    int getCounter() const {
//        return mCounter;
//    }
//
//    rrc::MessagePtr tryGetMessage();
//
//    ~DummyNode();
//
//private:
//    rrc::RootNodePtr mRootNode;
//    int mCounter;
//    std::string mTopicName;
//    rrc::QueueMessageListenerPtr mListener;
//};
//
//
