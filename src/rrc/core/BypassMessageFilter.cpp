/**
 * @author arssivka
 * @date 9/30/16
 */

#include <rrc/core/BypassMessageFilter.h>


bool rrc::BypassMessageFilter::accept(rrc::MessagePtr message) {
    return true;
}
