#include "Connection.hpp"

#include <iostream>
#include <string>
#include <exception>

int main() {
    std::string ip = "127.0.0.1";
    uint16_t port = 8080;
    int msg_size = 256;

    try {
        tcp::Connection connection(ip, port);
        connection.set_timeout(5);

        std::string msg(msg_size, '\0');
        std::string buf(msg_size, '\0');

        std::cout << "Enter your message: ";
        std::cin.getline(msg.data(), msg.size());
        connection.writeExact(msg.c_str(), msg_size);
        std::cout << "Sent: " << msg << std::endl;
        
        std::cout << "Waiting the message from server..." << std::endl;
        connection.read(buf.data(), msg_size);
        std::cout << "Received: " << buf << std::endl;

        std::cout << "Waiting the message from server..." << std::endl;
        connection.readExact(buf.data(), 16);
        std::cout << "Received: " << buf << std::endl;

        std::cout << "Enter your message: ";
        std::cin.getline(msg.data(), msg.size());
        connection.write(msg.c_str(), msg_size);
        std::cout << "Sent: " << msg << std::endl;

        connection.close();
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }
}
