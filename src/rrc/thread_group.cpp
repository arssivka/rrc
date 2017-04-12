/**
 *  @autor arssivka
 *  @date 4/9/17
 */

#include "rrc/thread_group.h"

rrc::thread_group::thread_group(size_t reserve) {
    if (reserve == 0) reserve = 1;
    m_threads.reserve(reserve);
}

void rrc::thread_group::add_thread(std::thread&& thread) {
    m_threads.push_back(std::move(thread));
}

void rrc::thread_group::join_all() {
    for (auto&& thread : m_threads) {
        if (thread.joinable()) thread.join();
    }
}

size_t rrc::thread_group::size() const noexcept {
    return m_threads.size();
}
