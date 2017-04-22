/**
 * The MIT License (MIT)
 * Copyright (c) 2015 Erik Rigtorp <erik@rigtorp.se>
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *  @autor arssivka
 *  @date 4/22/17
 *  @brief Ported functor class without heap allocation.
 *
 *  Wrap around the called objects. This class has a fixed size, which
 *  significantly improves the performance when creating an instance of the class.
 *  This class was written by Erik Rigtorp.
 */

#pragma once

#include <functional>
#include <memory>

namespace rrc {
    template<class, size_t MaxSize = 1024>
    class function;

    template<class R, class... Args, size_t MaxSize>
    class function<R(Args...), MaxSize> {
    public:
        function() noexcept {}

        function(std::nullptr_t) noexcept {}

        function(const function& other) {
            if (other) {
                other.m_manager(&m_data, &other.m_data, Operation::Clone);
                m_invoker = other.m_invoker;
                m_manager = other.m_manager;
            }
        }

        function(function&& other) { other.swap(*this); }

        template<class F>
        function(F&& f) {
            using f_type = typename std::decay<F>::type;
            static_assert(alignof(f_type) <= alignof(storage_t), "Invalid alignment");
            static_assert(sizeof(f_type) <= sizeof(storage_t), "Storage too small");
            new(&m_data) f_type(std::forward<F>(f));
            m_invoker = &invoke<f_type>;
            m_manager = &manage<f_type>;
        }

        ~function() {
            if (m_manager) {
                m_manager(&m_data, nullptr, Operation::Destroy);
            }
        }

        function& operator=(const function& other) {
            function(other).swap(*this);
            return *this;
        }

        function& operator=(function&& other) {
            function(std::move(other)).swap(*this);
            return *this;
        }

        function& operator=(std::nullptr_t) {
            if (m_manager) {
                m_manager(&m_data, nullptr, Operation::Destroy);
                m_manager = nullptr;
                m_invoker = nullptr;
            }
            return *this;
        }

        template<typename F>
        function& operator=(F&& f) {
            function(std::forward<F>(f)).swap(*this);
            return *this;
        }

        template<typename F>
        function& operator=(std::reference_wrapper<F> f) {
            function(f).swap(*this);
            return *this;
        }

        void swap(function& other) {
            std::swap(m_data, other.m_data);
            std::swap(m_manager, other.m_manager);
            std::swap(m_invoker, other.m_invoker);
        }

        explicit operator bool() const noexcept { return m_manager != nullptr; }

        R operator()(Args... args) {
            if (!m_invoker) {
                throw std::bad_function_call();
            }
            return m_invoker(&m_data, std::forward<Args>(args)...);
        }

    private:
        enum class Operation {
            Clone, Destroy
        };

        using invoker_t = R (*)(void*, Args&& ...);
        using manager_t = void (*)(void*, void*, Operation);
        using storage_t = typename std::aligned_storage<MaxSize - sizeof(invoker_t) - sizeof(manager_t), 8>::type;

        template<typename F>
        static R invoke(void* data, Args&& ... args) {
            F& f = *static_cast<F*>(data);
            return f(std::forward<Args>(args)...);
        }

        template<typename F>
        static void manage(void* dest, void* src, Operation op) {
            switch (op) {
                case Operation::Clone:
                    new(dest) F(*static_cast<F*>(src));
                    break;
                case Operation::Destroy:
                    static_cast<F*>(dest)->~F();
                    break;
            }
        }

        storage_t m_data;
        invoker_t m_invoker = nullptr;
        manager_t m_manager = nullptr;
    };
}

