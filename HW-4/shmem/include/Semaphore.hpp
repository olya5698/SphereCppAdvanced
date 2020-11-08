#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include <semaphore.h>

namespace shmem {

    class Semaphore {
    private:
        sem_t sem_;

    public:
        Semaphore(int pshared, unsigned int value);

        Semaphore(const Semaphore& other_sem) = delete;
        Semaphore& operator=(const Semaphore& other_sem) = delete;

        Semaphore(Semaphore&& other_sem) noexcept;
        Semaphore& operator=(Semaphore&& other_sem) noexcept;

        ~Semaphore();      

        void post();
        void wait();
        void destroy();
    };

} 

#endif 
