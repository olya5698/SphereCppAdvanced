#ifndef DESCRIPTOR_HPP
#define DESCRIPTOR_HPP

#include <memory>

namespace tcp {

    class Descriptor {
    private:
        int fd_;

    public:
        Descriptor() noexcept;
        explicit Descriptor(int fd) noexcept;

        Descriptor(const Descriptor& other_fd) = delete;
        Descriptor& operator=(const Descriptor& other_fd) = delete;

        Descriptor(Descriptor&& other_fd) noexcept;
        Descriptor& operator=(Descriptor&& other_fd) noexcept;

        ~Descriptor();      

        void set_fd(int fd) noexcept;
        int get_fd() noexcept;
        void close() noexcept;
    };

} 

#endif 
