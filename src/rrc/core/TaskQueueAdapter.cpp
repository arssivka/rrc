/**
 *  @autor arssivka
 *  @date 7/20/16
 */

#include <rrc/core/TaskQueueAdapter.h>


bool rrc::TaskQueueAdapter::execOnce() {
    Task task;
    if (this->tryDequeue(task)) {
        task();
        return true;
    }
    return false;
}


void rrc::TaskQueueAdapter::execAll() {
    Task task;
    while (this->tryDequeue(task)) {
        task();
    }
}