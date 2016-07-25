/**
 *  @autor arssivka
 *  @date 7/18/16
 */

#include "include/rrc/MessageSender.h"


void rrc::MessageSender::reset() {
    mCallback = [](ID, Message<pb::Message> msg, bool) -> bool { return true; };
}
