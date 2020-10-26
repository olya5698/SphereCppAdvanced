#include "Descriptor.hpp"

#include <iostream>
#include <string>
#include <utility>
#include <exception>
#include <cerrno>
#include <cstring>
#include <clocale>

int main() {  
    try {
        tcp::Descriptor desc1(1);
        tcp::Descriptor desc2(desc1.get_fd());
        tcp::Descriptor desc3(1);
        std::cout << "desc1 = " << desc1.get_fd() << ", " << "errno = " << errno << ' ' << std::strerror(errno) << std::endl;
        std::cout << "desc2 = " << desc2.get_fd() << ", " << "errno = " << errno << ' ' << std::strerror(errno) << std::endl;
        std::cout << "desc3 = " << desc3.get_fd() << ", " << "errno = " << errno << ' ' << std::strerror(errno) << std::endl;
        desc2.close();
        std::cout << "desc1 = " << desc1.get_fd() << ", " << "errno = " << errno << ' ' << std::strerror(errno) << std::endl;
        std::cout << "desc2 = " << desc2.get_fd() << ", " << "errno = " << errno << ' ' << std::strerror(errno) << std::endl;
        std::cout << "desc3 = " << desc3.get_fd() << ", " << "errno = " << errno << ' ' << std::strerror(errno) << std::endl;
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }
}
