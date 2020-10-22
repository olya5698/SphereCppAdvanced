#include "Descriptor.hpp"

#include <unistd.h>
#include <utility>
#include <sys/socket.h>
#include <exception>
#include <iostream>

namespace tcp {
    Descriptor::Descriptor() noexcept {}

    Descriptor::Descriptor(int fd) noexcept : fd_(fd) {}

    Descriptor::Descriptor(Descriptor&& other_fd) noexcept
        : fd_(std::move(other_fd.fd_)) {}

    Descriptor& Descriptor::operator=(Descriptor&& other_fd) noexcept {
        if (&other_fd == this) {
            return *this;
        }

        fd_ = std::move(other_fd.fd_);
        return *this;
    }

    Descriptor::~Descriptor() {
        try {
            close();
        }
        catch (const std::runtime_error& err) {
            std::cerr << err.what() << std::endl;
        }
    }

    void Descriptor::close() noexcept {
        if (fd_ != -1) {
            ::close(fd_);
            fd_ = -1;
        }
    }

    int Descriptor::get_fd() noexcept {
        if (fd_ != -1) {
            return fd_;
        }
        return -1;
    }

    void Descriptor::set_fd(int fd) noexcept {
    	close();
        fd_ = fd;
    }
}
