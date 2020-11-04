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
    try {
        size_t blocks_count = 100;
        size_t block_size = 128;
        size_t shmem_size = blocks_count * block_size;

        shmem::ShUTPtr<char> sh_mem = shmem::create_shmem<char>(shmem_size);
        shmem::ShMemState* state = new(sh_mem.get()) shmem::ShMemState{};

        float header_size = (sizeof(shmem::ShMemState) + blocks_count) / static_cast<float>(block_size);
        state->block_size = block_size;
        state->blocks_count = blocks_count - std::ceil(header_size);
        state->used_blocks_table = sh_mem.get() + sizeof(shmem::ShMemState);
        state->first_block = state->used_blocks_table + state->blocks_count;
        ::memset(state->used_blocks_table, shmem::FREE_BLOCK, state->blocks_count);

        shmem::ShAlloc<shmem::ShString> alloc{state};
        shmem::ShString* str = new(alloc.allocate(1)) shmem::ShString{alloc};

        pid_t pid = ::fork();

        if (pid == -1) {
            throw std::runtime_error("Fork error");
        }

        if (pid == 0) {
            *str = "Hello from Child!";
            return 0;
        }

        if (::waitpid(pid, nullptr, 0) == -1) {
            throw std::runtime_error("Waitpid error");
        }

        std::cout << *str << std::endl;
    } 
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}
