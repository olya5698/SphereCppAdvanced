#include "Server.hpp"

#include <iostream>
#include <string>
#include <exception>

int main() {
    std::string ip = "127.0.1.2";
    uint16_t port = 8888;
    int msg_size = 16;
    
    try {
        std::string buf(msg_size, '\0');
        std::string msg(msg_size, '\0');

        tcp::Server server(ip, port);
        server.set_timeout(5);

        tcp::Connection conn1(server.accept());

        std::cout << "Enter your message: ";
        std::cin.getline(msg.data(), msg.size());
        conn1.write(msg.c_str(), msg.size());
        std::cout << "Sent: " << msg << std::endl;

        std::cout << "Waiting the message from client1..." << std::endl;
        conn1.readExact(buf.data(), 8);
        std::cout << "Received: " << buf << std::endl;

        std::cout << "Waiting the message from client2..." << std::endl;
        tcp::Connection conn2(server.accept());

        conn2.read(buf.data(), 8);
        std::cout << "Received: " << buf << std::endl;

    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }
}
