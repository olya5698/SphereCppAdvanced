#ifndef SHAREDMEMORY_HPP
#define SHAREDMEMORY_HPP

#include <sys/mman.h>
#include <memory>
#include <functional>

namespace shmem {

    using ShString = std::basic_string<char, std::char_traits<char>, ShAlloc<char>>;

    template <typename T>
    using ShUTPtr = std::unique_ptr<T, std::function<void(T*)>>;

    template <typename T>
    ShUTPtr<T> create_shmem(size_t n = 1) {
        size_t shmem_size = sizeof(T) * n;

        void* mmap = ::mmap(0, shmem_size,
                    PROT_READ | PROT_WRITE,
                    MAP_ANONYMOUS | MAP_SHARED,
                    -1, 0);

        if (mmap == MAP_FAILED) {
            throw std::runtime_error("Failed to create shared mmap");
        }

        return {reinterpret_cast<T*>(mmap),
                    [shmem_size](T* t_shmem) { ::munmap(t_shmem, shmem_size); }};
    }

}

#endif
