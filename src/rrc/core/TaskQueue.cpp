/**
 *  @autor arssivka
 *  @date 7/20/16
 */

#include <rrc/core/TaskQueue.h>


bool rrc::TaskQueue::tryDequeue(rrc::Task& task) {
    return mTaskQueue.try_dequeue(task);
}


bool rrc::TaskQueue::execOnce() {
    Task task;
    if (mTaskQueue.try_dequeue(task)) {
        task();
        return true;
    }
    return false;
}


void rrc::TaskQueue::execAll() {
    Task task;
    while (mTaskQueue.try_dequeue(task)) {
        task();
    }
}
