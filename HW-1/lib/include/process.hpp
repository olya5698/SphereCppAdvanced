#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>
#include <vector>

namespace ns_process {

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
        int read_fd_;
        int write_fd_;
        pid_t proc_pid_;

        void close_fd(std::vector<int> fd_for_close);
    };
}

#endif
