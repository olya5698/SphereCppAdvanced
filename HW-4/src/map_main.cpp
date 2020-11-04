#include "SharedMap.hpp"
#include "SharedAllocator.hpp"
#include "SemLock.hpp"
#include "Semaphore.hpp"

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <wait.h>

int main() {
    try {
        size_t blocks_count = 100;
        size_t block_size = 128;

        shmem::SharedMap<int, shmem::ShString> map(block_size, blocks_count);
        shmem::ShAlloc<char> alloc(map.get_allocator().state_);

        map.insert({1, {7, '1', alloc}});
        map.insert({2, {8, '2', alloc}});
        map.insert({3, {9, '3', alloc}});

        pid_t pid = ::fork();

        if (pid == -1) {
            throw std::runtime_error("Fork error");
        }

        if (pid == 0) {
            std::cout << "Child process" << std::endl;

            auto it = map.begin();
            while (it != map.end()) {
                std::cout << it->first << ' ' << it->second << std::endl;
                it++;
            }

            map.insert({4, {6, '4', alloc}});
            map.update({2, {5, '7', alloc}});
            map.remove(3);
            std::cout << "map.get(2): " << map.get(2) << std::endl;

        } else {
            ::sleep(2);
            std::cout << "Parent process" << std::endl;
            map.insert({5, {5, '5', alloc}});
            
            auto it = map.begin();
            while (it != map.end()) {
                std::cout << it->first << ' ' << it->second << std::endl;
                it++;
            }

            map.destroy();

            if (::waitpid(pid, nullptr, 0) == -1) {
                throw std::runtime_error("Waitpid error");
            }
        }

    } 
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}