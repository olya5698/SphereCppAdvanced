#include "Semaphore.hpp"

#include <string>
#include <exception>
#include <iostream>

namespace shmem {
    
    Semaphore::Semaphore(int pshared, unsigned int value) {
        if (::sem_init(&sem_, pshared, value) == -1) {
            throw std::runtime_error("Semaphore init error");
        }
    }

    Semaphore::Semaphore(Semaphore&& other_sem) noexcept {
        sem_ = std::move(other_sem.sem_);
        other_sem.destroy();
    }

    Semaphore& Semaphore::operator=(Semaphore&& other_sem) noexcept {
        destroy();

        if (&other_sem == this) {
            return *this;
        }

        sem_ = std::move(other_sem.sem_);
        other_sem.destroy();

        return *this;
    }

    Semaphore::~Semaphore() {
        try {
            destroy();
        } 
        catch (const std::runtime_error& err) {
            std::cerr << err.what() << std::endl;
        }
    }   

    void Semaphore::post() {
        if (::sem_post(&sem_) == -1) {
            throw std::runtime_error("Semaphore post error");
        }
    }

    void Semaphore::wait() {
        if (::sem_wait(&sem_) == -1) {
            throw std::runtime_error("Semaphore wait error");
        }
    }

    void Semaphore::destroy() {
        if (::sem_destroy(&sem_) == -1) {
            throw std::runtime_error("Semaphore destroy error");
        }
    }
}
