#include "process.hpp"

#include <iostream>
#include <cstring>
#include <exception>

void cat_process(const std::string& path, std::string& buf, const std::string& str) {
    ns_process::Process process1(path);
    process1.writeExact(str.c_str(), str.size());
    process1.closeStdin();
    process1.readExact(buf.data(), str.size());
    process1.close();
    std::cout << buf << std::endl;
}

void date_process(const std::string& path, std::string& buf) {
    ns_process::Process process2(path);
    process2.read(buf.data(), buf.size());
    process2.close();
    std::cout << buf << std::endl;
}

int main() {
    try {
        const std::string path1 = "/usr/bin/cat";
        std::string buf(32, '\0');
        const std::string str = "Hello world!";
        cat_process(path1, buf, str);
    }
    catch(const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }

    try {
        const std::string path2 = "/usr/bin/date";
        std::string buf(32, '\0');
        date_process(path2, buf);
    }
    catch(const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }
    
    return 0;
}
