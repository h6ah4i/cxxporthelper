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

#include <cxxporthelper/aligned_memory.hpp>

#include <cassert>
#include <cstring>

#include <cxxporthelper/cstdint>

namespace cxxporthelper {

template <typename T>
static inline bool is_pow_of_two(T x) CXXPH_NOEXCEPT
{
    static_assert(std::is_integral<T>::value, "value requires integral type");
    return ((x > 0) && ((x & (x - 1)) == 0));
}

void *aligned_memory_static_impl::alloc_aligned(std::size_t size, std::size_t alignment, bool zero_clear) CXXPH_NOEXCEPT
{
    // check alignment size
    assert(is_pow_of_two(alignment));

    const size_t ptr_size = sizeof(void *);
    const size_t actual_alignment = (alignment > ptr_size) ? alignment : ptr_size;
    const size_t actual_alloc_size = size + (actual_alignment - 1) + ptr_size;

    // allocate memory
    void *ptr = ::operator new(actual_alloc_size);

    if (!ptr)
        return nullptr;

    if (zero_clear) {
        ::memset(ptr, 0, actual_alloc_size);
    }

    uintptr_t ptr_addr = reinterpret_cast<uintptr_t>(ptr);

    uintptr_t aligned_addr = (ptr_addr + actual_alignment) & ~(actual_alignment - 1);
    void *aligned_ptr = reinterpret_cast<void *>(aligned_addr);

    // store original allocated address
    static_cast<void **>(aligned_ptr)[-1] = ptr;

    return aligned_ptr;
}

void aligned_memory_static_impl::free_aligned(void *ptr) CXXPH_NOEXCEPT
{
    if (ptr) {
        // obtain original allocated address
        void *allocated_ptr = static_cast<void **>(ptr)[-1];

        ::operator delete(allocated_ptr);
    }
}

} // namespace cxxporthelper
