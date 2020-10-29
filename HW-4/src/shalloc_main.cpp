#include "SharedAllocator.hpp"
#include "SharedMap.hpp"

#include <iostream>
#include <memory>
#include <cmath>
#include <cerrno>
#include <cstring>
#include <functional>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main() {
    size_t blocks_count = 100;
    size_t block_size = 128;
    size_t shmem_size = blocks_count * block_size;
    void* mmap = ::mmap(0, shmem_size,
                        PROT_READ | PROT_WRITE,
                        MAP_ANONYMOUS | MAP_SHARED,
                        -1, 0);

    if(mmap == MAP_FAILED) {
        std::cerr << "Failed to create shared map" << std::endl;
        return 1;
    }

    ShUPtr shmem{static_cast<char*>(mmap),
                [shmem_size](char* shmem) { ::munmap(shmem, shmem_size); }};

    ShMemState* state = new(shmem.get()) ShMemState{};

    float header_size = (sizeof(ShMemState) + blocks_count) / static_cast<float>(block_size);
    state->block_size = block_size;
    state->blocks_count = blocks_count - std::floor(header_size);
    state->used_blocks_table = shmem.get() + sizeof(ShMemState);
    state->first_block = state->used_blocks_table + state->blocks_count;
    ::memset(state->used_blocks_table, FREE_BLOCK, state->blocks_count);

    ShAlloc<ShString> alloc{state};
    ShString* string = new(alloc.allocate(1)) ShString{alloc};

    int fork = ::fork();
    if (fork == 0) {
        *string = "Hello from Child!";
        return 0;
    }

    ::waitpid(fork, nullptr, 0);
    std::cout << *string << std::endl;

    return 0;
}
