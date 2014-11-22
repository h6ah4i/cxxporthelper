//
//    Copyright (C) 2014 Haruki Hasegawa
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//

#ifndef CXXPORTHELPER_ATOMIC_COMPAT_HPP_
#define CXXPORTHELPER_ATOMIC_COMPAT_HPP_

#include <cxxporthelper/cstdint>
#include <cxxporthelper/cstddef>

namespace cxxporthelper {
namespace atomic_compat {

//
// memory_order
//
enum memory_order {
    memory_order_relaxed = __ATOMIC_RELAXED,
    memory_order_consume = __ATOMIC_CONSUME,
    memory_order_acquire = __ATOMIC_ACQUIRE,
    memory_order_release = __ATOMIC_RELEASE,
    memory_order_acq_rel = __ATOMIC_ACQ_REL,
    memory_order_seq_cst = __ATOMIC_SEQ_CST
};

//
// atomic<T>
//
template <typename T>
class atomic {
public:
    // constructors
    atomic() = default;
    constexpr atomic(T desired) : value_(desired) {}
    atomic(const atomic &) = delete;

    // is_lock_free
    bool is_lock_free() const;
    bool is_lock_free() const volatile;

    // store
    void store(T desired, memory_order order = memory_order_seq_cst);
    void store(T desired, memory_order order = memory_order_seq_cst) volatile;

    // load
    T load(memory_order order = memory_order_seq_cst) const;
    T load(memory_order order = memory_order_seq_cst) const volatile;

    // add
    T fetch_add(T arg, memory_order order = memory_order_seq_cst);
    T fetch_add(T arg, memory_order order = memory_order_seq_cst) volatile;

    // sub
    T fetch_sub(T arg, memory_order order = memory_order_seq_cst);
    T fetch_sub(T arg, memory_order order = memory_order_seq_cst) volatile;

    // and
    T fetch_and(T arg, memory_order order = memory_order_seq_cst);
    T fetch_and(T arg, memory_order order = memory_order_seq_cst) volatile;

    // or
    T fetch_or(T arg, memory_order order = memory_order_seq_cst);
    T fetch_or(T arg, memory_order order = memory_order_seq_cst) volatile;

    // exclusive-or
    T fetch_xor(T arg, memory_order order = memory_order_seq_cst);
    T fetch_xor(T arg, memory_order order = memory_order_seq_cst) volatile;

    // exchange
    T exchange(T desired, memory_order order = memory_order_seq_cst);
    T exchange(T desired, memory_order order = memory_order_seq_cst) volatile;

    // compare_exchange_weak
    bool compare_exchange_weak(T &expected, T desired, memory_order success, memory_order failure);
    bool compare_exchange_weak(T &expected, T desired, memory_order success, memory_order failure) volatile;

    bool compare_exchange_weak(T &expected, T desired, memory_order order = memory_order_seq_cst);
    bool compare_exchange_weak(T &expected, T desired, memory_order order = memory_order_seq_cst) volatile;

    // compare_exchange_strong
    bool compare_exchange_strong(T &expected, T desired, memory_order success, memory_order failure);
    bool compare_exchange_strong(T &expected, T desired, memory_order success, memory_order failure) volatile;

    bool compare_exchange_strong(T &expected, T desired, memory_order order = memory_order_seq_cst);
    bool compare_exchange_strong(T &expected, T desired, memory_order order = memory_order_seq_cst) volatile;

    // operator T
    operator T() const;
    operator T() const volatile;

    // operator++ (pre-increment)
    T operator++();
    T operator++() volatile;

    // operator++ (post-increment)
    T operator++(int);
    T operator++(int) volatile;

    // operator-- (pre-decrement)
    T operator--();
    T operator--() volatile;

    // operator-- (post-decrement)
    T operator--(int);
    T operator--(int) volatile;

    // operator+=
    T operator+=(T arg);
    T operator+=(T arg) volatile;

    // operator-=
    T operator-=(T arg);
    T operator-=(T arg) volatile;

    // operator&=
    T operator&=(T arg);
    T operator&=(T arg) volatile;

    // operator|=
    T operator|=(T arg);
    T operator|=(T arg) volatile;

    // operator^=
    T operator^=(T arg);
    T operator^=(T arg) volatile;

private:
    // add
    T add_fetch(T arg, memory_order order = memory_order_seq_cst);
    T add_fetch(T arg, memory_order order = memory_order_seq_cst) volatile;

    // sub
    T sub_fetch(T arg, memory_order order = memory_order_seq_cst);
    T sub_fetch(T arg, memory_order order = memory_order_seq_cst) volatile;

    // and
    T and_fetch(T arg, memory_order order = memory_order_seq_cst);
    T and_fetch(T arg, memory_order order = memory_order_seq_cst) volatile;

    // or
    T or_fetch(T arg, memory_order order = memory_order_seq_cst);
    T or_fetch(T arg, memory_order order = memory_order_seq_cst) volatile;

    // exclusive-or
    T xor_fetch(T arg, memory_order order = memory_order_seq_cst);
    T xor_fetch(T arg, memory_order order = memory_order_seq_cst) volatile;

private:
    T value_;
};

// atomic<T>::is_lock_free
template <typename T>
inline bool atomic<T>::is_lock_free() const
{
    return ::__atomic_is_lock_free(sizeof(T), &value_);
}

template <typename T>
inline bool atomic<T>::is_lock_free() const volatile
{
    return ::__atomic_is_lock_free(sizeof(T), &value_);
}

// atomic<T>::store
template <typename T>
inline void atomic<T>::store(T desired, memory_order order)
{
    ::__atomic_store(&value_, &desired, order);
}

template <typename T>
inline void atomic<T>::store(T desired, memory_order order) volatile
{
    ::__atomic_store(&value_, &desired, order);
}

// atomic<T>::load
template <typename T>
inline T atomic<T>::load(memory_order order) const
{
    T ret = 0;
    ::__atomic_load(&value_, &ret, order);
    return ret;
}

template <typename T>
inline T atomic<T>::load(memory_order order) const volatile
{
    T ret = 0;
    ::__atomic_load(&value_, &ret, order);
    return ret;
}

// atomic<T>::fetch_add
template <typename T>
inline T atomic<T>::fetch_add(T arg, memory_order order)
{
    return __atomic_fetch_add(&value_, arg, order);
}

template <typename T>
inline T atomic<T>::fetch_add(T arg, memory_order order) volatile
{
    return __atomic_fetch_add(&value_, arg, order);
}

// atomic<T>::fetch_sub
template <typename T>
inline T atomic<T>::fetch_sub(T arg, memory_order order)
{
    return __atomic_fetch_sub(&value_, arg, order);
}

template <typename T>
inline T atomic<T>::fetch_sub(T arg, memory_order order) volatile
{
    return __atomic_fetch_sub(&value_, arg, order);
}

// atomic<T>::fetch_and
template <typename T>
inline T atomic<T>::fetch_and(T arg, memory_order order)
{
    return __atomic_fetch_and(&value_, arg, order);
}

template <typename T>
inline T atomic<T>::fetch_and(T arg, memory_order order) volatile
{
    return __atomic_fetch_and(&value_, arg, order);
}

// atomic<T>::fetch_or
template <typename T>
inline T atomic<T>::fetch_or(T arg, memory_order order)
{
    return __atomic_fetch_or(&value_, arg, order);
}

template <typename T>
inline T atomic<T>::fetch_or(T arg, memory_order order) volatile
{
    return __atomic_fetch_or(&value_, arg, order);
}

// atomic<T>::fetch_xor
template <typename T>
inline T atomic<T>::fetch_xor(T arg, memory_order order)
{
    return __atomic_fetch_xor(&value_, arg, order);
}

template <typename T>
inline T atomic<T>::fetch_xor(T arg, memory_order order) volatile
{
    return __atomic_fetch_xor(&value_, arg, order);
}

// atomic<T>::exchange
template <typename T>
inline T atomic<T>::exchange(T desired, memory_order order)
{
    return ::__atomic_exchange(&value_, &desired, order);
}

template <typename T>
inline T atomic<T>::exchange(T desired, memory_order order) volatile
{
    return ::__atomic_exchange(&value_, &desired, order);
}

// atomic<T>::compare_exchange_weak
template <typename T>
inline bool atomic<T>::compare_exchange_weak(T &expected, T desired, memory_order success, memory_order failure)
{
    return ::__atomic_compare_exchange(&value_, &expected, &desired, true, success, failure);
}

template <typename T>
inline bool atomic<T>::compare_exchange_weak(T &expected, T desired, memory_order success,
                                             memory_order failure) volatile
{
    return ::__atomic_compare_exchange(&value_, &expected, &desired, true, success, failure);
}

template <typename T>
inline bool atomic<T>::compare_exchange_weak(T &expected, T desired, memory_order order)
{
    return ::__atomic_compare_exchange(&value_, &expected, &desired, true, order, order);
}

template <typename T>
inline bool atomic<T>::compare_exchange_weak(T &expected, T desired, memory_order order) volatile
{
    return ::__atomic_compare_exchange(&value_, &expected, &desired, true, order, order);
}

// atomic<T>::compare_exchange_strong
template <typename T>
inline bool atomic<T>::compare_exchange_strong(T &expected, T desired, memory_order success, memory_order failure)
{
    return ::__atomic_compare_exchange(&value_, &expected, &desired, false, success, failure);
}

template <typename T>
inline bool atomic<T>::compare_exchange_strong(T &expected, T desired, memory_order success,
                                               memory_order failure) volatile
{
    return ::__atomic_compare_exchange(&value_, &expected, &desired, false, success, failure);
}

template <typename T>
inline bool atomic<T>::compare_exchange_strong(T &expected, T desired, memory_order order)
{
    return ::__atomic_compare_exchange(&value_, &expected, &desired, false, order, order);
}

template <typename T>
inline bool atomic<T>::compare_exchange_strong(T &expected, T desired, memory_order order) volatile
{
    return ::__atomic_compare_exchange(&value_, &expected, &desired, false, order, order);
}

// atomic<T>::operator T
template <typename T>
inline atomic<T>::operator T() const
{
    return load();
}

template <typename T>
inline atomic<T>::operator T() const volatile
{
    return load();
}

// atomic<T>::operator++ (pre-increment)
template <typename T>
inline T atomic<T>::operator++()
{
    return add_fetch(static_cast<T>(1));
}

template <typename T>
inline T atomic<T>::operator++() volatile
{
    return add_fetch(static_cast<T>(1));
}

// atomic<T>::operator++ (post-increment)
template <typename T>
inline T atomic<T>::operator++(int)
{
    return fetch_add(static_cast<T>(1));
}

template <typename T>
inline T atomic<T>::operator++(int) volatile
{
    return fetch_add(static_cast<T>(1));
}

// atomic<T>::operator-- (pre-decrement)
template <typename T>
inline T atomic<T>::operator--()
{
    return sub_fetch(static_cast<T>(1));
}

template <typename T>
inline T atomic<T>::operator--() volatile
{
    return sub_fetch(static_cast<T>(1));
}

// atomic<T>::operator-- (post-decrement)
template <typename T>
inline T atomic<T>::operator--(int)
{
    return fetch_sub(static_cast<T>(1));
}

template <typename T>
inline T atomic<T>::operator--(int) volatile
{
    return fetch_sub(static_cast<T>(1));
}

// atomic<T>::operator+=
template <typename T>
inline T atomic<T>::operator+=(T arg)
{
    return add_fetch(arg);
}

template <typename T>
inline T atomic<T>::operator+=(T arg) volatile
{
    return add_fetch(arg);
}

// operator-=
template <typename T>
inline T atomic<T>::operator-=(T arg)
{
    return sub_fetch(arg);
}

template <typename T>
inline T atomic<T>::operator-=(T arg) volatile
{
    return sub_fetch(arg);
}

// operator&=
template <typename T>
inline T atomic<T>::operator&=(T arg)
{
    return and_fetch(arg);
}

template <typename T>
inline T atomic<T>::operator&=(T arg) volatile
{
    return and_fetch(arg);
}

// operator|=
template <typename T>
inline T atomic<T>::operator|=(T arg)
{
    return or_fetch(arg);
}

template <typename T>
inline T atomic<T>::operator|=(T arg) volatile
{
    return or_fetch(arg);
}

// operator^=
template <typename T>
inline T atomic<T>::operator^=(T arg)
{
    return xor_fetch(arg);
}

template <typename T>
inline T atomic<T>::operator^=(T arg) volatile
{
    return xor_fetch(arg);
}

// atomic<T>::add_fetch
template <typename T>
inline T atomic<T>::add_fetch(T arg, memory_order order)
{
    return __atomic_add_fetch(&value_, arg, order);
}

template <typename T>
inline T atomic<T>::add_fetch(T arg, memory_order order) volatile
{
    return __atomic_add_fetch(&value_, arg, order);
}

// atomic<T>::sub_fetch
template <typename T>
inline T atomic<T>::sub_fetch(T arg, memory_order order)
{
    return __atomic_sub_fetch(&value_, arg, order);
}

template <typename T>
inline T atomic<T>::sub_fetch(T arg, memory_order order) volatile
{
    return __atomic_sub_fetch(&value_, arg, order);
}

// atomic<T>::and_fetch
template <typename T>
inline T atomic<T>::and_fetch(T arg, memory_order order)
{
    return __atomic_and_fetch(&value_, arg, order);
}

template <typename T>
inline T atomic<T>::and_fetch(T arg, memory_order order) volatile
{
    return __atomic_and_fetch(&value_, arg, order);
}

// atomic<T>::or_fetch
template <typename T>
inline T atomic<T>::or_fetch(T arg, memory_order order)
{
    return __atomic_or_fetch(&value_, arg, order);
}

template <typename T>
inline T atomic<T>::or_fetch(T arg, memory_order order) volatile
{
    return __atomic_or_fetch(&value_, arg, order);
}

// atomic<T>::xor_fetch
template <typename T>
inline T atomic<T>::xor_fetch(T arg, memory_order order)
{
    return __atomic_xor_fetch(&value_, arg, order);
}

template <typename T>
inline T atomic<T>::xor_fetch(T arg, memory_order order) volatile
{
    return __atomic_xor_fetch(&value_, arg, order);
}

//
// typedefs of atomic<T>
//
typedef atomic<char> atomic_char;
typedef atomic<signed char> atomic_schar;
typedef atomic<unsigned char> atomic_uchar;
typedef atomic<short> atomic_short;
typedef atomic<unsigned short> atomic_ushort;
typedef atomic<int> atomic_int;
typedef atomic<unsigned int> atomic_uint;
typedef atomic<long> atomic_long;
typedef atomic<unsigned long> atomic_ulong;
typedef atomic<long long> atomic_llong;
typedef atomic<unsigned long long> atomic_ullong;
typedef atomic<char16_t> atomic_char16_t;
typedef atomic<char32_t> atomic_char32_t;
typedef atomic<wchar_t> atomic_wchar_t;
typedef atomic<std::int_least8_t> atomic_int_least8_t;
typedef atomic<std::uint_least8_t> atomic_uint_least8_t;
typedef atomic<std::int_least16_t> atomic_int_least16_t;
typedef atomic<std::uint_least16_t> atomic_uint_least16_t;
typedef atomic<std::int_least32_t> atomic_int_least32_t;
typedef atomic<std::uint_least32_t> atomic_uint_least32_t;
typedef atomic<std::int_least64_t> atomic_int_least64_t;
typedef atomic<std::uint_least64_t> atomic_uint_least64_t;
typedef atomic<std::int_fast8_t> atomic_int_fast8_t;
typedef atomic<std::uint_fast8_t> atomic_uint_fast8_t;
typedef atomic<std::int_fast16_t> atomic_int_fast16_t;
typedef atomic<std::uint_fast16_t> atomic_uint_fast16_t;
typedef atomic<std::int_fast32_t> atomic_int_fast32_t;
typedef atomic<std::uint_fast32_t> atomic_uint_fast32_t;
typedef atomic<std::int_fast64_t> atomic_int_fast64_t;
typedef atomic<std::uint_fast64_t> atomic_uint_fast64_t;
typedef atomic<std::intptr_t> atomic_intptr_t;
typedef atomic<std::uintptr_t> atomic_uintptr_t;
typedef atomic<std::intmax_t> atomic_intmax_t;
typedef atomic<std::uintmax_t> atomic_uintmax_t;
typedef atomic<std::size_t> atomic_size_t;
typedef atomic<std::ptrdiff_t> atomic_ptrdiff_t;

typedef atomic<bool> atomic_bool; // NOTE: not correct, it should be specialized atomic_flag class

//
// atomic operations
//

inline void atomic_thread_fence(int memmodel) { ::__atomic_thread_fence(memmodel); }

inline void atomic_signal_fence(int memmodel) { ::__atomic_signal_fence(memmodel); }

//
// ATOMIC_VAR_INIT
//
#ifndef ATOMIC_VAR_INIT
#define ATOMIC_VAR_INIT(x) (x)
#endif

} // namespace atomic_compat
} // namespace cxxporthelper

#endif /* CXXPORTHELPER_ATOMIC_COMPAT_HPP_ */
