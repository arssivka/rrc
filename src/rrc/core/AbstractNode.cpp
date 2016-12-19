/**
 *  @autor arssivka
 *  @date 11/21/16
 */

#include <rrc/core/AbstractNode.h>
#include <include/rrc/core/EngineWrapper.h>


rrc::AbstractNode::AbstractNode(rrc::EngineWrapper engineWrapper)
        : mEngineWrapper(engineWrapper) {}


rrc::EngineWrapper rrc::AbstractNode::getEngineWrapper() const {
    return mEngineWrapper;
}


rrc::AbstractNode::~AbstractNode() { }
