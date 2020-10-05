#include "../include/process.hpp"

#include <iostream>
#include <cstring>

using namespace std;
using namespace hw1_process;

int main() {
        string path = "/usr/bin/cat";
        string str = "Hello world!";
        string buf(32,'\0');
        
        Process process1(path);
        process1.writeExact(str.c_str(), str.size());
        process1.closeStdin();
        process1.readExact(buf.data(), str.size());
        process1.close();
    std::cout << buf << endl;

        path = "/usr/bin/date";
        Process process2(path);
        process2.read(buf.data(), buf.size());
        process2.close();
    std::cout << buf << endl;

    return 0;
}
