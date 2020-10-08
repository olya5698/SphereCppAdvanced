#include "process.hpp"

#include <iostream>
#include <cstring>
#include <exception>

using namespace hw1_process;

int main() {
    std::string path = "/usr/bin/cat";
    std::string str = "Hello world!";
    std::string buf(32,'\0');

    try {
        Process process1(path);
        process1.writeExact(str.c_str(), str.size());
        process1.closeStdin();
        process1.readExact(buf.data(), str.size());
        process1.close();
        std::cout << buf << std::endl;

        path = "/usr/bin/date";
        Process process2(path);
        process2.read(buf.data(), buf.size());
        process2.close();
        std::cout << buf << std::endl;
    }

    catch(std::runtime_error err) {
        std::cout << err.what() << std::endl;
    }
    
    return 0;
}
