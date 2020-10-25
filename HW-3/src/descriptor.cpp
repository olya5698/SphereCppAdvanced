#include "Server.hpp"
#include "Connection.hpp"
#include "Descriptor.hpp"

#include <iostream>
#include <string>
#include <utility>
#include <exception>

int main() {  
    try {
        tcp::Descriptor desc1;
        desc1.set_fd(4);
        tcp::Descriptor desc2 = std::move(desc1);
        tcp::Descriptor desc3(4);
        
        std::cout << desc1.get_fd() << std::endl;
        std::cout << desc2.get_fd() << std::endl;
        std::cout << desc3.get_fd() << std::endl;
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }
}
