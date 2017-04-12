/**
 *  @autor arssivka
 *  @date 4/9/17
 */

#pragma once


#include <thread>
#include <vector>

namespace rrc {
    class thread_group {
    public:
        thread_group(size_t reserve = 1);

        void add_thread(std::thread&& thread);

        void join_all();

        size_t size() const noexcept;

    private:
        std::vector<std::thread> m_threads;
    };
}


