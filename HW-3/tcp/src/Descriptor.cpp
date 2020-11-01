#include "Descriptor.hpp"

#include <unistd.h>
#include <utility>
#include <sys/socket.h>
#include <exception>

namespace tcp {
    Descriptor::Descriptor() noexcept : fd_(-1) {}

    Descriptor::Descriptor(int fd) noexcept {
        fd_ = ::dup(fd);
    }

    Descriptor::Descriptor(Descriptor&& other_fd) noexcept {
        fd_ = std::move(other_fd.fd_);
        other_fd.set_fd(-1);
    }

    Descriptor& Descriptor::operator=(Descriptor&& other_fd) noexcept {
        close();

        if (&other_fd == this) {
            return *this;
        }

        fd_ = std::move(other_fd.fd_);
        other_fd.set_fd(-1);

        return *this;
    }

    Descriptor::~Descriptor() {
        close();
    }

    void Descriptor::close() noexcept {
        if (fd_ >= 0) {
            ::close(fd_);
            fd_ = -1;
        }
    }

    int Descriptor::get_fd() noexcept {
        return fd_;
    }

    void Descriptor::set_fd(int fd) noexcept {
        fd_ = ::dup(fd);
    }
}
