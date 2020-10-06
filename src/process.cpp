#include "process.hpp"

#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <exception>

using namespace std;

namespace hw1_process {

    Process::Process(const std::string &path) {

        int pipe1_fd[2], pipe2_fd[2];

        if (pipe(pipe1_fd) == -1) {
            perror("Pipe1 Error");
            exit(1);
        }

        if (pipe(pipe2_fd) == -1) {
            perror("Pipe2 Error");
            ::close(pipe1_fd[0]);
            ::close(pipe1_fd[1]);
            exit(1);
        }

        proc_pid = fork();

        if (proc_pid == -1) {
            perror("Fork Error");
            ::close(pipe1_fd[0]);
            ::close(pipe1_fd[1]);
            ::close(pipe2_fd[0]);
            ::close(pipe2_fd[1]);
            exit(1);

        } else if (proc_pid == 0) {

            if (dup2(pipe1_fd[0], STDIN_FILENO) == -1) {
                perror("Dup2 STDIN Error");
                ::close(pipe1_fd[0]);
                ::close(pipe1_fd[1]);
                ::close(pipe2_fd[0]);
                ::close(pipe2_fd[1]);
                exit(1);
            }

            if (dup2(pipe2_fd[1], STDOUT_FILENO) == -1) {
                perror("Dup2 STDOUT Error");
                ::close(pipe1_fd[0]);
                ::close(pipe1_fd[1]);
                ::close(pipe2_fd[0]);
                ::close(pipe2_fd[1]);
                exit(1);
            }

            ::close(pipe1_fd[0]);
            ::close(pipe1_fd[1]);
            ::close(pipe2_fd[0]);
            ::close(pipe2_fd[1]);

            if (execl(path.c_str(), path.c_str(), nullptr) == -1) {
                perror("Execl Error");
                exit(1);
            }

        } else {
            read_fd = pipe2_fd[0];
            write_fd = pipe1_fd[1];
        }
    }

    Process::~Process() {
        Process::close();
    }

    size_t Process::write(const void *data, size_t len) {
        ssize_t wbytes = ::write(write_fd, data, len);
        if (wbytes == -1) {
            perror("Write Error");
            exit(1);
        }
        return wbytes;
    }

    void Process::writeExact(const void *data, size_t len) {
        ssize_t wbytes = 0;
        const char *data_start = static_cast<const char *>(data);
        while (wbytes != len) {
            data_start += wbytes;
            wbytes += Process::write(data_start, len - wbytes);
        }
    }

    size_t Process::read(void *data, size_t len) {
        ssize_t rbytes = ::read(read_fd, data, len);
        if (rbytes == -1) {
            perror("Read Error");
            exit(1);
        }

        return rbytes;
    }

    void Process::readExact(void *data, size_t len) {
        ssize_t rbytes = 0;
        char *data_start = static_cast<char *>(data);
        while (rbytes != len) {
            data_start += rbytes;
            rbytes += Process::read(data_start, len - rbytes);
        }
    }

    void Process::closeStdin() {
        ::close(write_fd);
    }

    void Process::close() {
        if (proc_pid) {
            ::close(write_fd);
            ::close(read_fd);

            if (kill(proc_pid, SIGINT) == -1) {
                perror("Kill Error");
                exit(1);
            }

            if (waitpid(proc_pid, nullptr, 0) == -1) {
                perror("Waitpid Error");
                exit(1);
            }

            proc_pid = 0;
        }
    }

}