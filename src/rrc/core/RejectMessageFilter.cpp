/**
 * @author arssivka
 * @date 9/30/16
 */

#include <rrc/core/RejectMessageFilter.h>


bool rrc::RejectMessageFilter::accept(rrc::MessagePtr message) {
    return false;
}
