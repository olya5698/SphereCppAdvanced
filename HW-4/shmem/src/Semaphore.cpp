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
