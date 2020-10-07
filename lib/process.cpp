#include "process.hpp"

#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <exception>
#include <vector>

using namespace std;

namespace hw1_process {

    Process::Process(const std::string &path) {

        int pipe1_fd[2]; 
        int pipe2_fd[2];

        if (::pipe(pipe1_fd) == -1) {
            ::perror("Pipe1 Error");
            ::exit(1);
        }

        if (::pipe(pipe2_fd) == -1) {
            ::perror("Pipe2 Error");
            vector<int> vector_fd = {pipe1_fd[0], pipe1_fd[1]};
            Process::close_fd(vector_fd);
            ::exit(1);
        }

        proc_pid = ::fork();

        if (proc_pid == -1) {
            ::perror("Fork Error");
            vector<int> vector_fd = {pipe1_fd[0], pipe1_fd[1], pipe2_fd[0], pipe2_fd[1]};
            Process::close_fd(vector_fd);
            ::exit(1);

        } else if (proc_pid == 0) {

            if (::dup2(pipe1_fd[0], STDIN_FILENO) == -1) {
                ::perror("Dup2 STDIN Error");
                vector<int> vector_fd = {pipe1_fd[0], pipe1_fd[1], pipe2_fd[0], pipe2_fd[1]};
                Process::close_fd(vector_fd);
                ::exit(1);
            }

            if (::dup2(pipe2_fd[1], STDOUT_FILENO) == -1) {
                ::perror("Dup2 STDOUT Error");
                vector<int> vector_fd = {pipe1_fd[0], pipe1_fd[1], pipe2_fd[0], pipe2_fd[1]};
                Process::close_fd(vector_fd);
                ::exit(1);
            }

            vector<int> vector_fd = {pipe1_fd[0], pipe1_fd[1], pipe2_fd[0], pipe2_fd[1]};
            Process::close_fd(vector_fd);

            if (::execl(path.c_str(), path.c_str(), nullptr) == -1) {
                ::perror("Execl Error");
                ::exit(1);
            }

        } else {
            read_fd = pipe2_fd[0];
            write_fd = pipe1_fd[1];
            vector<int> vector_fd = {pipe1_fd[0], pipe2_fd[1]};
            Process::close_fd(vector_fd);
        }
    }

    Process::~Process() {
        Process::close();
    }

    size_t Process::write(const void *data, size_t len) {
        if (write_fd == -1) {
            ::perror("Writing to closed descriptor aborted");
            ::exit(1);
        }
        ssize_t bytes_written = ::write(write_fd, data, len);
        if (bytes_written == -1) {
            ::perror("Write Error");
            ::exit(1);
        }
        return bytes_written;
    }

    void Process::writeExact(const void *data, size_t len) {
        ssize_t bytes_written = 0;
        const char *data_start = static_cast<const char *>(data);
        while (bytes_written != len) {
            data_start += bytes_written;
            bytes_written += Process::write(data_start, len - bytes_written);
        }
    }

    size_t Process::read(void *data, size_t len) {
        if (read_fd == -1) {
            ::perror("Reading from closed descriptor aborted");
            ::exit(1);
        }
        ssize_t bytes_read = ::read(read_fd, data, len);
        if (bytes_read == -1) {
            ::perror("Read Error");
            ::exit(1);
        }

        return bytes_read;
    }

    void Process::readExact(void *data, size_t len) {
        ssize_t bytes_read = 0;
        char *data_start = static_cast<char *>(data);
        while (bytes_read != len) {
            data_start += bytes_read;
            bytes_read += Process::read(data_start, len - bytes_read);
        }
    }

    void Process::closeStdin() {
        if (write_fd == -1) {
            ::perror("Closing the closed descriptor aborted");
            ::exit(1);
        }
        vector<int> vector_fd = {write_fd};
        Process::close_fd(vector_fd);
    }

    void Process::close() {
        if (proc_pid) {
            if (write_fd == -1 || read_fd == -1) {
                ::perror("Closing the closed descriptor aborted");
                ::exit(1);
            }
            vector<int> vector_fd = {read_fd, write_fd};
            Process::close_fd(vector_fd);

            if (::kill(proc_pid, SIGINT) == -1) {
                ::perror("Kill Error");
                ::exit(1);
            }

            if (::waitpid(proc_pid, nullptr, 0) == -1) {
                ::perror("Waitpid Error");
                ::exit(1);
            }

            proc_pid = 0;
        }
    }

    void Process::close_fd(std::vector<int> &fd_for_close) {
        for (int i = 0; i < fd_for_close.size(); i++) {
            ::close(fd_for_close[i]);
            fd_for_close[i] = -1;
        }
    }

}
