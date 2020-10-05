#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>

namespace hw1_process {

    class Process {
    public:
        explicit Process(const std::string& path);
        ~Process();
        size_t write(const void* data, size_t len);
        void writeExact(const void* data, size_t len);
        size_t read(void* data, size_t len);
        void readExact(void* data, size_t len);
        void closeStdin();
        void close();

    private:
        int read_fd;
        int write_fd;
        pid_t proc_pid;

    };
}

#endif