#include "Connection.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <utility>
#include <exception>
#include <iostream>

namespace tcp {

    Connection::Connection() {
         conn_fd_.set_fd(-1);
    }

    Connection::Connection(int fd) {
        conn_fd_.set_fd(fd);
        fd = -1;
    }

    Connection::Connection(const std::string& addr, uint16_t port) {
        int fd = ::socket(AF_INET, SOCK_STREAM, 0);

        if (fd == -1) {
            throw std::runtime_error("Creating socket error");
        }

        conn_fd_.set_fd(fd);

        sockaddr_in connection_addr{};
        connection_addr.sin_family = AF_INET;
        connection_addr.sin_port = ::htons(port);

        if (::inet_aton(addr.c_str(), &connection_addr.sin_addr) == 0) {
            throw std::runtime_error("Invalid IP host address in connection");
        }

        if (::connect(conn_fd_.get_fd(), reinterpret_cast<sockaddr*>(&connection_addr), sizeof(connection_addr)) == -1) {
            throw std::runtime_error("Connection error");
        }
    }

    Connection::Connection(Connection&& other_connection) noexcept {
        conn_fd_ = std::move(other_connection.conn_fd_);
        other_connection.conn_fd_.set_fd(-1);
    }

    Connection& Connection::operator=(Connection&& other_connection) noexcept {
        close();

        if (&other_connection == this) {
            return *this;
        }

        conn_fd_ = std::move(other_connection.conn_fd_);
        other_connection.conn_fd_.set_fd(-1);

        return *this;
    }

    void Connection::connect(const std::string& addr, uint16_t port) {
        close();

        int fd = ::socket(AF_INET, SOCK_STREAM, 0);

        if (fd == -1) {
            throw std::runtime_error("Creating socket error");
        }

        conn_fd_.set_fd(fd);

        sockaddr_in connection_addr{};
        connection_addr.sin_family = AF_INET;
        connection_addr.sin_port = ::htons(port);

        if (::inet_aton(addr.c_str(), &connection_addr.sin_addr) == 0) {
            throw std::runtime_error("Invalid IP host address in connection");
        }

        if (::connect(conn_fd_.get_fd(), reinterpret_cast<sockaddr*>(&connection_addr), sizeof(connection_addr)) == -1) {
            throw std::runtime_error("Connection error");
        }
    }

    void Connection::close() {
        conn_fd_.close();
    }

    size_t Connection::write(const char* data, size_t len) {
        if (conn_fd_.get_fd() == -1) {
            throw std::runtime_error("Writing to closed descriptor aborted");
        }

        size_t bytes_written = ::write(conn_fd_.get_fd(), data, len);

        if (bytes_written == -1) {
            throw std::runtime_error("Write error");
        }

        return bytes_written;
    } 

    void Connection::writeExact(const char* data, size_t len) {
        size_t bytes_written = 0;
        const char* data_start = data;

        while (bytes_written != len) {
            data_start += bytes_written;
            size_t bytes_written_part = write(data_start, len - bytes_written);

            if (bytes_written_part == 0) {
                throw std::runtime_error("Zero bytes written");
            }

            bytes_written += bytes_written_part;
        }
    }

    size_t Connection::read(char* data, size_t len) {
        if (conn_fd_.get_fd() == -1) {
            throw std::runtime_error("Reading from closed descriptor aborted");
        }

        size_t bytes_read = ::read(conn_fd_.get_fd(), data, len);

        if (bytes_read == -1) {
            throw std::runtime_error("Read error");
        }

        return bytes_read;
    }

    void Connection::readExact(char* data, size_t len) {
        size_t bytes_read = 0;
        char* data_start = data;

        while (bytes_read != len) {
            data_start += bytes_read;
            size_t bytes_read_part = read(data_start, len - bytes_read);
            
            if (bytes_read_part == 0) {
                throw std::runtime_error("Zero bytes read");
            }

            bytes_read += bytes_read_part;
        }
    }

    void Connection::set_timeout(long sec) {
        timeval timeout{.tv_sec = sec, .tv_usec = 0};

        if (setsockopt(conn_fd_.get_fd(), 
                SOL_SOCKET,
                SO_SNDTIMEO | SO_RCVTIMEO,
                &timeout,
                sizeof(timeout)) < 0) {
            throw std::runtime_error("Set timeout error");
        }
    }

}
