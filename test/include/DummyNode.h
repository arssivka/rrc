/**
 *  @autor arssivka
 *  @date 9/2/16
 */

#pragma once


#include <rrc/core/Node.h>
#include <rrc/core/RootNode.h>
#include <rrc/core/MessageListener.h>

class DummyNode : public rrc::Node {
public:
    DummyNode(rrc::RootNodePtr rootNode, const std::string& topicName);

    virtual void entry() override {
        this->incrementCounter();
    }

    void incrementCounter();

    void resetCounter();

    int getCounter() const {
        return mCounter;
    }

    rrc::MessagePtr tryGetMessage();

    ~DummyNode();

private:
    rrc::RootNodePtr mRootNode;
    int mCounter;
    std::string mTopicName;
    rrc::MessageListenerPtr mListener;
};


