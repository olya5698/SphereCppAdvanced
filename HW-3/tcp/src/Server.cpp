#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <utility>
#include <exception>
#include <iostream>

#include "Server.hpp"

namespace tcp {

    Server::Server() {
        server_fd_.set_fd(-1);
    }

    Server::Server(const std::string& addr, uint16_t port, int max_connection) {        
        int fd = ::socket(AF_INET, SOCK_STREAM, 0);

        if (fd == -1) {
            throw std::runtime_error("Creating socket error");
        }

        server_fd_.set_fd(fd);

        sockaddr_in server_addr{};
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = ::htons(port);

        if (::inet_aton(addr.c_str(), &server_addr.sin_addr) == 0) {
            throw std::runtime_error("Invalid IP host address in server");
        }

        if (::bind(server_fd_.get_fd(), reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
            throw std::runtime_error("Socket binding error");
        }

        set_max_connect(max_connection);
    }

    Server::Server(Server&& other_server) noexcept {
        server_fd_ = std::move(other_server.server_fd_);
        other_server.server_fd_.set_fd(-1);
    }

    Server& Server::operator=(Server&& other_server) noexcept {
        close();

        if (&other_server == this) {
            return *this;
        }

        server_fd_ = std::move(other_server.server_fd_);
        other_server.server_fd_.set_fd(-1);

        return *this;
    }

    void Server::open(const std::string& addr, uint16_t port, int max_connection) {
        close();

        int fd = ::socket(AF_INET, SOCK_STREAM, 0);

        if (fd == -1) {
            throw std::runtime_error("Creating socket error");
        }

        server_fd_.set_fd(fd);

        sockaddr_in server_addr{};
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = ::htons(port);

        if (::inet_aton(addr.c_str(), &server_addr.sin_addr) == 0) {
            throw std::runtime_error("Invalid IP host address in server");
        }

        if (::bind(server_fd_.get_fd(), reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
            throw std::runtime_error("Socket binding error");
        }

        set_max_connect(max_connection);
    }

    void Server::set_max_connect(int max_connection) {
        if (::listen(server_fd_.get_fd(), max_connection) == -1) {
            throw std::runtime_error("Socket listen error");
        }
    }

    Connection Server::accept() {
        sockaddr_in client_addr{};
        socklen_t client_addr_size = sizeof(client_addr);

        int client_fd = ::accept(server_fd_.get_fd(), reinterpret_cast<sockaddr*>(&client_addr), &client_addr_size);
        
        if (client_fd == -1) {
            throw std::runtime_error("Socket accept error");
        }

        return Connection(client_fd);
    }

    void Server::close() {
        server_fd_.close();
    }

    void Server::set_timeout(long sec) {
        timeval timeout{.tv_sec = sec, .tv_usec = 0};

        if (setsockopt(server_fd_.get_fd(),
                SOL_SOCKET,
                SO_SNDTIMEO | SO_RCVTIMEO,
                &timeout,
                sizeof(timeout)) < 0) {
            throw std::runtime_error("Set timeout error");
        }
    }

}
