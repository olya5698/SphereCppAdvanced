#ifndef SERVER_HPP
#define SERVER_HPP

#include "Connection.hpp"
#include <sys/socket.h>

namespace tcp {

    class Server {
    private:
        Descriptor server_fd_;

    public:
        Server();
        Server(const std::string& addr, uint16_t port, int max_connection = SOMAXCONN);

        Server(const Server& other_server) = delete;
        Server& operator=(const Server& other_server) = delete;

        Server(Server&& other_server) noexcept;
        Server& operator=(Server&& other_server) noexcept;

        void open(const std::string& addr, uint16_t port, int max_connection = SOMAXCONN);
        void close();

        Connection accept();
        void set_max_connect(int max_connection);

        void set_timeout(long ms);

    };

}

#endif
