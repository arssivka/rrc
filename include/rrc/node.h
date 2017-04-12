/**
 *  @autor arssivka
 *  @date 4/8/17
 */

#pragma once


#include "defines.h"
#include <string>
#include <unordered_map>

namespace rrc {
    class sender;
    class receiver;

    class RRC_EXPORT node {
        node(const node&) = delete;

        node& operator=(const node&) = delete;

    public:
        node() = default;

        node(node&&) = default;

        node& operator=(node&&) = default;

        virtual void on_init();

        virtual void on_start();

        virtual void on_finish();

        virtual void on_process();

        virtual ~node();

        void add_sender(const std::string& key,
                        sender* sender_ptr);

        void add_receiver(const std::string& key,
                          receiver* receiver_ptr);

        sender* find_sender(const std::string& key) const noexcept;

        receiver* find_receiver(const std::string& key) const noexcept;

    private:
        std::unordered_map<std::string, sender*> m_senders_hash;
        std::unordered_map<std::string, receiver*> m_receivers_hash;
    };
}


