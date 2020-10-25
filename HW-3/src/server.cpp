#include "Server.hpp"

#include <iostream>
#include <string>
#include <exception>

int main() {
    std::string ip = "127.0.1.2";
    uint16_t port = 8888;
    int msg_size = 16;
    int buf_size = 12;
    
    try {
        std::string msg(msg_size, '\0');
        std::string buf(buf_size, '\0');

        tcp::Server server(ip, port);
        server.set_timeout(5);

        tcp::Connection conn1(server.accept());

        std::cout << "Enter your message: ";
        std::cin.getline(msg.data(), msg_size);
        conn1.write(msg.data(), msg_size);
        std::cout << "Sent: " << msg << std::endl;

        std::cout << "Waiting the message from client1..." << std::endl;
        conn1.readExact(buf.data(), buf_size);
        std::cout << "Received: " << buf << std::endl;

        std::cout << "Waiting the message from client2..." << std::endl;
        tcp::Connection conn2(server.accept());

        conn2.read(buf.data(), buf_size);
        std::cout << "Received: " << buf << std::endl;

    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }
}
