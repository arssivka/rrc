/**
 *  @autor arssivka
 *  @date 4/11/17
 */

#pragma once


#include <forward_list>

namespace rrc {
    class sender;
    class receiver;

    class topic {
    public:
        void add_sender(sender* sender_ptr);

        void add_receiver(receiver* receiver_ptr);

        void reset();

        void connect();

    private:
        std::forward_list<sender*> m_senders;
        std::forward_list<receiver*> m_receivers;
    };
}


