/**
 *  @autor arssivka
 *  @date 4/8/17
 */

#pragma once


#include <vector>
#include <string>

namespace rrc {
    class receiver;

    class sender {
    public:
        void add_receiver(receiver* rec_ptr);

        void remove_receiver(receiver* rec_ptr);

        void send(const std::string& str);

        void send(const uint8_t* buff, size_t size);

        size_t receivers_count() const noexcept;

        bool connected() const noexcept;

        void disconnect_all();

        bool has_receiver(const receiver* receiver_ptr) const noexcept;

    private:
        std::vector<receiver*> m_receivers_vector;

    };
}


