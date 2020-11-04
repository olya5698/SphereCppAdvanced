#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include <semaphore.h>

namespace shmem {

    class Semaphore {
    private:
        sem_t sem_;

    public:
        explicit Semaphore(int pshared, unsigned int value);

        Semaphore(const Semaphore& other_sem) = delete;
        Semaphore& operator=(const Semaphore& other_sem) = delete;

        ~Semaphore() noexcept;      

        void post();
        void wait();
        void destroy();
    };

} 

#endif 
