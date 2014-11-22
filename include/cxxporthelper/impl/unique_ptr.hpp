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

#ifndef CXXPORTHELPER_UNIQUE_PTR_HPP_

#include <cxxporthelper/type_traits>
#include <cxxporthelper/utility>
#include <cxxporthelper/cstddef>
#include <cxxporthelper/compiler.hpp>

namespace cxxporthelper {
namespace memory {

/**
 * default deleter  (single object version).
 *
 * @tparam T Object type
 */
template <class T>
struct default_delete {
    /**
     * operator() - Delete object.
     */
    void operator()(T *ptr) const { delete ptr; }
};

/**
 * default deleter  (array version).
 *
 * @tparam T Object type
 */
template <class T>
struct default_delete<T[]> {
    /**
     * operator() - Delete array.
     */
    void operator()(T *ptr) { delete[] ptr; }
};

namespace details {

// D is non-reference type D""
template <typename D>
struct deleter_signatures_resolver {
    typedef const D &type1;
    typedef D &&type2;
};

//  D is an lvalue-reference type "D&"
template <typename D>
struct deleter_signatures_resolver<D &> {
    typedef std::remove_reference<D> &type1;
    typedef std::remove_reference<D> &&type2;
};

//  D is an lvalue-reference type "const D&"
template <typename D>
struct deleter_signatures_resolver<const D &> {
    typedef const std::remove_const<std::remove_reference<D>> &type1;
    typedef const std::remove_const<std::remove_reference<D>> &&type2;
};

} // namespace details

/**
 * unique_ptr  (single object version).
 *
 * @tparam T Element type
 * @tparam Deleter Deleter object type
 *
 * @note This class does not support implicit cast operations.
 */
template <class T, class Deleter = cxxporthelper::memory::default_delete<T>>
class unique_ptr {
public:
    typedef T *pointer;
    typedef T element_type;
    typedef Deleter deleter_type;

    /**
     * Default constructor.
     */
    unique_ptr() : ptr_(nullptr), deleter_() {}

    /**
     * Constructor.
     * @param p [in] pointer
     */
    explicit unique_ptr(pointer p) : ptr_(p), deleter_() {}

    /**
     * nullptr_t constructor.
     */
    unique_ptr(std::nullptr_t) : ptr_(nullptr), deleter_() {}

    /**
     * Constructor.
     * @param p [in] pointer
     * @param d2 [in] deleter
     */
    unique_ptr(pointer p, typename details::deleter_signatures_resolver<Deleter>::type1 d1) : ptr_(p), deleter_(d1) {}

    /**
     * Constructor.
     * @param p [in] pointer
     * @param d2 [in] deleter
     */
    unique_ptr(pointer p, typename details::deleter_signatures_resolver<Deleter>::type2 d2)
        : ptr_(p), deleter_(std::forward<typename details::deleter_signatures_resolver<Deleter>::type2>(d2))
    {
    }

    /**
     * Move constructor.
     * @param p [in] pointer
     */
    unique_ptr(unique_ptr &&u) : ptr_(u.ptr_), deleter_(u.deleter_) { u.ptr_ = nullptr; }

    /**
     * Destructor.
     */
    ~unique_ptr() { reset(); }

    /**
     * Release pointer.
     *
     * @returns pointer
     */
    pointer release() CXXPH_NOEXCEPT
    {
        pointer p = ptr_;
        ptr_ = nullptr;
        return p;
    }

    /**
     * Reset pointer.
     *
     * @param p [in] Pointer
     */
    void reset(pointer p = pointer()) CXXPH_NOEXCEPT
    {
        if (p == ptr_)
            return;

        deleter_(ptr_);
        ptr_ = p;
    }

    /**
     * Swap.
     *
     * @param other [in] Other unique_ptr
     *
     */
    void swap(unique_ptr &other) CXXPH_NOEXCEPT
    {
        if (&other == this) {
            return;
        }

        pointer p = ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = p;
    }

    /**
     * Get pointer.
     *
     * @returns Pointer
     */
    pointer get() const CXXPH_NOEXCEPT { return ptr_; }

    /**
     * Get deleter object.
     *
     * @returns Reference to the deleter object
     */
    /// @{
    deleter_type &get_deleter() CXXPH_NOEXCEPT { return deleter_; }

    const deleter_type &get_deleter() const CXXPH_NOEXCEPT { return deleter_; }
    /// @}

    /**
     * operator 'bool'
     *
     * @returns Whether the pointer is vaild.
     */
    operator bool() const CXXPH_NOEXCEPT { return ptr_; }

    /**
     * operator '='   (move operation)
     */
    unique_ptr &operator=(unique_ptr &&other)
    {
        move(std::forward<unique_ptr &&>(other));
        return (*this);
    }

    /**
     * operator '='   (reset operation)
     */
    unique_ptr &operator=(std::nullptr_t)
    {
        reset();
        return (*this);
    }

    /**
     * operator '*'
     *
     * @returns Owned object.
     */
    /// @{
    element_type &operator*() const { return (*ptr_); }
    /// @}

    /**
     * operator '->'
     *
     * @returns Owned object.
     */
    /// @{
    pointer operator->() const CXXPH_NOEXCEPT { return ptr_; }
    /// @}

    /// @cond INTERNAL_FIELD
    unique_ptr(const unique_ptr &) = delete;
    unique_ptr &operator=(const unique_ptr &) = delete;
    /// @endcond

private:
    void move(unique_ptr &&u) CXXPH_NOEXCEPT
    {
        if (CXXPH_UNLIKELY(&u == this)) {
            return;
        }

        reset();

        ptr_ = u.ptr_;
        deleter_ = u.deleter_;

        u.ptr_ = nullptr;
    }

private:
    element_type *ptr_;
    deleter_type deleter_;
};

/**
 * unique_ptr  (array version).
 *
 * @tparam T Element type
 * @tparam Deleter Deleter object type
 *
 * @note This class does not support implicit cast operations.
 */
template <class T, class Deleter>
class unique_ptr<T[], Deleter> {
public:
    typedef T *pointer;
    typedef T element_type;
    typedef Deleter deleter_type;

    /**
     * Default constructor.
     */
    unique_ptr() : ptr_(nullptr), deleter_() {}

    /**
     * Constructor.
     * @param p [in] pointer
     */
    explicit unique_ptr(pointer p) : ptr_(p), deleter_() {}

    /**
     * nullptr_t constructor.
     */
    unique_ptr(std::nullptr_t) : ptr_(nullptr), deleter_() {}

    /**
     * Constructor.
     * @param p [in] pointer
     * @param d2 [in] deleter
     */
    unique_ptr(pointer p, typename details::deleter_signatures_resolver<Deleter>::type1 d1) : ptr_(p), deleter_(d1) {}

    /**
     * Constructor.
     * @param p [in] pointer
     * @param d2 [in] deleter
     */
    unique_ptr(pointer p, typename details::deleter_signatures_resolver<Deleter>::type2 d2)
        : ptr_(p), deleter_(std::forward<typename details::deleter_signatures_resolver<Deleter>::type2>(d2))
    {
    }

    /**
     * Move constructor.
     * @param p [in] pointer
     */
    unique_ptr(unique_ptr &&u) : ptr_(u.ptr_), deleter_(u.deleter_) { u.ptr_ = nullptr; }

    /**
     * Destructor.
     */
    ~unique_ptr() { reset(); }

    /**
     * Release pointer.
     *
     * @returns pointer
     */
    pointer release() CXXPH_NOEXCEPT
    {
        pointer p = ptr_;
        ptr_ = nullptr;
        return p;
    }

    /**
     * Reset pointer.
     *
     * @param p [in] Pointer
     */
    void reset(pointer p = pointer()) CXXPH_NOEXCEPT
    {
        if (CXXPH_UNLIKELY(p == ptr_))
            return;

        deleter_type deleter;
        deleter(ptr_);
        ptr_ = p;
    }

    /**
     * Swap.
     *
     * @param other [in] Other unique_ptr
     *
     */
    void swap(unique_ptr &other) CXXPH_NOEXCEPT
    {
        if (CXXPH_UNLIKELY(&other == this)) {
            return;
        }

        pointer p = ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = p;
    }

    /**
     * Get pointer.
     *
     * @returns Pointer
     */
    pointer get() const CXXPH_NOEXCEPT { return ptr_; }

    /**
     * Get deleter object.
     *
     * @returns Reference to the deleter object
     */
    /// @{
    deleter_type &get_deleter() CXXPH_NOEXCEPT { return deleter_; }

    const deleter_type &get_deleter() const CXXPH_NOEXCEPT { return deleter_; }
    /// @}

    /**
     * operator 'bool'
     *
     * @returns Whether the pointer is vaild.
     */
    operator bool() const CXXPH_NOEXCEPT { return ptr_; }

    /**
     * operator '='   (move operation)
     */
    unique_ptr &operator=(unique_ptr &&other)
    {
        move(std::forward<unique_ptr &&>(other));
        return (*this);
    }

    /**
     * operator '='   (reset operation)
     */
    unique_ptr &operator=(std::nullptr_t)
    {
        reset();
        return (*this);
    }

    /**
     * operator '[]'
     *
     * @param i [in] index
     * @returns Reference to object[i].
     */
    element_type &operator[](int i) const { return ptr_[i]; }

private:
    void move(unique_ptr &&u) CXXPH_NOEXCEPT
    {
        if (CXXPH_UNLIKELY(&u == this)) {
            return;
        }

        reset();

        ptr_ = u.ptr_;
        deleter_ = u.deleter_;

        u.ptr_ = nullptr;
    }

private:
    element_type *ptr_;
    deleter_type deleter_;
};

/*
 * Operators.
 */
#define DECL_UNIQUE_PTR_OPERATORS(operator_str)                                                                        \
    template <class T1, class D1, class T2, class D2>                                                                  \
    inline bool operator operator_str(const unique_ptr<T1, D1> &lhs, const unique_ptr<T2, D2> &rhs)                    \
    {                                                                                                                  \
        return (lhs.get() operator_str rhs.get());                                                                     \
    }                                                                                                                  \
                                                                                                                       \
    template <class T, class D>                                                                                        \
    inline bool operator operator_str(const unique_ptr<T, D> &lhs, std::nullptr_t) CXXPH_NOEXCEPT                      \
    {                                                                                                                  \
        return (lhs.get() operator_str nullptr);                                                                       \
    }                                                                                                                  \
                                                                                                                       \
    template <class T, class D>                                                                                        \
    inline bool operator operator_str(std::nullptr_t, const unique_ptr<T, D> &rhs) CXXPH_NOEXCEPT                      \
    {                                                                                                                  \
        return (nullptr operator_str rhs.get());                                                                       \
    }

DECL_UNIQUE_PTR_OPERATORS(== )
DECL_UNIQUE_PTR_OPERATORS(!= )
DECL_UNIQUE_PTR_OPERATORS(< )
DECL_UNIQUE_PTR_OPERATORS(<= )
DECL_UNIQUE_PTR_OPERATORS(> )
DECL_UNIQUE_PTR_OPERATORS(>= )

} // namespace memory
} // namespace cxxporthelper

#endif // CXXPORTHELPER_UNIQUE_PTR_HPP_
