#ifndef SEMLOCK_HPP
#define SEMLOCK_HPP

#include "Semaphore.hpp"

namespace shmem {

    class SemLock {
    private:
        Semaphore& semaphore_;

    public:
        explicit SemLock(Semaphore& semaphore);
        ~SemLock();
    };

}

#endif
