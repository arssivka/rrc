/**
 *  @autor arssivka
 *  @date 11/21/16
 */

#include <rrc/core/Node.h>


rrc::Node::Node(rrc::EngineWrapper engineWrapper)
        : mEngineWrapper(engineWrapper) {}


rrc::EngineWrapper rrc::Node::getEngineWrapper() const {
    return mEngineWrapper;
}


rrc::Node::~Node() { }
