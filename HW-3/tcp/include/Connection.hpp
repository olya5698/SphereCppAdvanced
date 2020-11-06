#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <string>
#include <netinet/in.h>

#include "Descriptor.hpp"

namespace tcp {

    class Connection {
    private:
        Descriptor conn_fd_;

    public:
        Connection() noexcept;
        explicit Connection(int fd) noexcept;
        Connection(const std::string& addr, uint16_t port);

        Connection(const Connection& other_connection) = delete;
        Connection& operator=(const Connection& other_connection) = delete;

        Connection(Connection&& other_connection) noexcept;
        Connection& operator=(Connection&& other_connection) noexcept;

        void connect(const std::string& addr, uint16_t port);
        void close();

        size_t read(char* data, size_t len);
        size_t write(const char* data, size_t len);
        void readExact(char* data, size_t len);
        void writeExact(const char* data, size_t len);

        void set_timeout(long sec);

    };

}

#endif
