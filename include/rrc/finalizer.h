/**
 *  @autor arssivka
 *  @date 3/1/17
 */
#pragma once


#include <functional>
#include <memory>
#include <forward_list>

namespace rrc {
    class finalizer {
    public:
        typedef std::function<void()> callback_type;

        void add_callback(std::shared_ptr<callback_type> callback_ptr);

        void remove_callback(std::shared_ptr<callback_type> callback_ptr);

        void exec_all();
    private:
        std::forward_list<std::shared_ptr<callback_type>> m_callback_list;

    };
}

