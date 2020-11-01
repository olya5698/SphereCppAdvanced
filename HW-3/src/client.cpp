#include "Connection.hpp"

#include <iostream>
#include <string>
#include <exception>

int main() {
    std::string ip = "127.0.0.1";
    uint16_t port = 8080;
    int msg_size = 16;
    int buf_size = 12;

    try {
        tcp::Connection connection;
        connection.connect(ip, port);
        connection.set_timeout(5);

        std::string msg(msg_size, '\0');
        std::string buf(buf_size, '\0');

        std::cout << "Enter your message: ";
        std::cin.getline(msg.data(), msg_size);
        connection.writeExact(msg.data(), msg_size);
        std::cout << "Sent: " << msg << std::endl;
        
        std::cout << "Waiting the message from server..." << std::endl;
        connection.read(buf.data(), buf_size);
        std::cout << "Received: " << buf << std::endl;

        std::cout << "Waiting the message from server..." << std::endl;
        connection.readExact(buf.data(), buf_size);
        std::cout << "Received: " << buf << std::endl;

        std::cout << "Enter your message: ";
        std::cin.getline(msg.data(), msg_size);
        connection.write(msg.data(), msg_size);
        std::cout << "Sent: " << msg << std::endl;

        connection.close();
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }
}
