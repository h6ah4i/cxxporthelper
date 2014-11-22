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

#ifndef CXXPORTHELPER_ALIGNED_MEMORY_H_
#define CXXPORTHELPER_ALIGNED_MEMORY_H_

#include <new>

#include <cxxporthelper/cstddef>
#include <cxxporthelper/type_traits>
#include <cxxporthelper/utility>
#include <cxxporthelper/memory>
#include <cxxporthelper/compiler.hpp>
#include <cxxporthelper/platform_info.hpp>

namespace cxxporthelper {

/// @cond INTERNAL_FIELD
class aligned_memory_static_impl {
public:
    aligned_memory_static_impl() = delete;

    static void *alloc_aligned(std::size_t size, std::size_t alignment, bool zero_clear) CXXPH_NOEXCEPT;
    static void free_aligned(void *ptr) CXXPH_NOEXCEPT;
};
/// @endcond

template <typename T>
struct aligned_memory_allocator {
    T *operator()(std::size_t alignment, bool zero_clear) const CXXPH_NOEXCEPT
    {
        return static_cast<T *>(aligned_memory_static_impl::alloc_aligned(sizeof(T) * 1, alignment, zero_clear));
    }
};

template <typename T>
struct aligned_memory_allocator<T[]> {
    T *operator()(std::size_t n, std::size_t alignment, bool zero_clear) const CXXPH_NOEXCEPT
    {
        return static_cast<T *>(aligned_memory_static_impl::alloc_aligned(sizeof(T) * n, alignment, zero_clear));
    }
};

template <typename T>
struct aligned_memory_deleter {
    void operator()(T *ptr) const CXXPH_NOEXCEPT
    {
        if (ptr) {
            aligned_memory_static_impl::free_aligned(ptr);
        }
    }
};

template <typename T>
struct aligned_memory_deleter<T[]> {
    void operator()(T *ptr) const CXXPH_NOEXCEPT
    {
        if (ptr) {
            aligned_memory_static_impl::free_aligned(ptr);
        }
    }
};

/**
 * Aligned memory allocator.
 *
 * @tparam T data type
 */
template <typename T>
class aligned_memory {

    /// @cond INTERNAL_FIELD
    aligned_memory(const aligned_memory &) = delete;
    aligned_memory &operator=(const aligned_memory &) = delete;
    /// @endcond

public:
    /**
     * Data type
     */
    typedef T data_type;

    /**
     * Size type
     */
    typedef std::size_t size_type;

    /**
     * Allocator type.
     */
    typedef aligned_memory_allocator<T[]> allocator_type;

    /**
     * Deleter type.
     */
    typedef aligned_memory_deleter<T[]> deleter_type;

    enum { DEFAULT_ALIGNMENT = CXXPH_PLATFORM_CACHE_LINE_SIZE };

    /**
     * Constructor.
     */
    aligned_memory() CXXPH_NOEXCEPT : ptr_(), size_(0) {}

    /**
     * Constructor.
     *
     * @param size [in] size of allocation block (unit: data_type element)
     * @param alignment [in] memory alignment [bytes]
     * @param zero_clear [in] zero filling
     */
    aligned_memory(size_type size, std::size_t alignment = DEFAULT_ALIGNMENT, bool zero_clear = true) : ptr_(), size_(0)
    {
        allocate(size, alignment, zero_clear);
    }

    /**
     * Move constructor
     */
    aligned_memory(aligned_memory &&other) CXXPH_NOEXCEPT : ptr_(), size_(0) { move(other); }

    /**
     * Destructor.
     */
    ~aligned_memory() { free(); }

    /**
     * Allocate memory
     *
     * @param size [in] size of allocation block (unit: data_type element)
     * @param alignment [in] memory alignment [bytes]
     * @param zero_clear [in] zero filling
     */
    void allocate(size_type size, std::size_t alignment = DEFAULT_ALIGNMENT, bool zero_clear = true)
    {
        // free current allocated memory
        free();

        // allocate new memory area
        allocator_type allocator;
        T *ptr = allocator(size, alignment, zero_clear);

        if (!ptr) {
            throw new std::bad_alloc();
        }

        // update fields
        ptr_.reset(ptr);
        size_ = size;
    }

    /**
     * Free allocated memory.
     */
    void free() CXXPH_NOEXCEPT
    {
        ptr_.reset();
        size_ = 0;
    }

    /**
     * Get pointer of the buffer.
     *
     * @returns pointer to the allocated buffer
     */
    /// @{
    T *get() CXXPH_NOEXCEPT { return ptr_; }

    const T *get() const CXXPH_NOEXCEPT { return ptr_; }
    /// @}

    /**
     * Array accessor operator
     *
     * @param index [in] index of the buffer  (index >= 0 && index < size())
     * @returns reference to the buffer item
     */
    /// @{
    T &operator[](int index)CXXPH_NOEXCEPT { return ptr_[index]; }

    const T &operator[](int index) const CXXPH_NOEXCEPT { return ptr_[index]; }
    /// @}

    /**
     * Get buffer size.
     *
     * @returns size of the allocated buffer (unit: data_type element)
     */
    size_type size() const CXXPH_NOEXCEPT { return size_; }

    /**
     * 'bool' operator.
     *
     * @returns whether the buffer is allocated
     */
    explicit operator bool() const CXXPH_NOEXCEPT { return static_cast<bool>(ptr_); }

    /**
     * Move operation.
     */
    /// @{
    aligned_memory &operator=(aligned_memory &&other) CXXPH_NOEXCEPT
    {
        if (this == &other) {
            return (*this);
        }

        free();
        move(std::forward<aligned_memory &&>(other));

        return (*this);
    }
    /// @}

private:
    /// @cond INTERNAL_FIELD
    void move(aligned_memory &&other) CXXPH_NOEXCEPT
    {
        ptr_ = std::move(other.ptr_);

        size_ = other.size_;
        other.size_ = 0;
    }

    std::unique_ptr<T[], deleter_type> ptr_;
    size_type size_;
    /// @endcond
};

} // namespace cxxporthelper

#endif // CXXPORTHELPER_ALIGNED_MEMORY_H_
