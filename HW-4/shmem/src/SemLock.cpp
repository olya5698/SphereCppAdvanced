#include "SemLock.hpp"
#include "Semaphore.hpp"

#include <utility>
#include <iostream>

namespace shmem {

    SemLock::SemLock(Semaphore& semaphore)
        : semaphore_(semaphore) {
        semaphore_.wait();
    }

    SemLock::~SemLock() {
        try {
            semaphore_.post();
        } 
        catch (const std::runtime_error& err) {
            std::cerr << err.what() << std::endl;
        }
    }

}
