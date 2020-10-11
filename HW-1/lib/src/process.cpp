#include "process.hpp"

#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <exception>
#include <vector>

namespace ns_process {

    Process::Process(const std::string &path) {

        int pipe1_fd[2]; 
        int pipe2_fd[2];

        if (::pipe(pipe1_fd) == -1) {
            throw std::runtime_error("Pipe1 Error");
        }

        if (::pipe(pipe2_fd) == -1) {
            close_fd({pipe1_fd[0], pipe1_fd[1]});
            throw std::runtime_error("Pipe2 Error");
        }

        proc_pid_ = ::fork();

        if (proc_pid_ == -1) {
            close_fd({pipe1_fd[0], pipe1_fd[1], pipe2_fd[0], pipe2_fd[1]});
            throw std::runtime_error("Fork Error");

        } else if (proc_pid_ == 0) {

            if (::dup2(pipe1_fd[0], STDIN_FILENO) == -1) {
                close_fd({pipe1_fd[0], pipe1_fd[1], pipe2_fd[0], pipe2_fd[1]});
                throw std::runtime_error("Dup2 STDIN Error");
            }

            if (::dup2(pipe2_fd[1], STDOUT_FILENO) == -1) {
                close_fd({pipe1_fd[0], pipe1_fd[1], pipe2_fd[0], pipe2_fd[1]});
                throw std::runtime_error("Dup2 STDOUT Error");
            }

            close_fd({pipe1_fd[0], pipe1_fd[1], pipe2_fd[0], pipe2_fd[1]});

            if (::execl(path.c_str(), path.c_str(), nullptr) == -1) {
                throw std::runtime_error("Execl Error");
            }

        } else {
            read_fd_ = pipe2_fd[0];
            write_fd_ = pipe1_fd[1];
            close_fd({pipe1_fd[0], pipe2_fd[1]});
        }
    }

    Process::~Process() {
        try {
            close();
        }
        catch (const std::runtime_error& err) {
            std::cerr << err.what() << std::endl;
        }
    }


    size_t Process::write(const void *data, size_t len) {
        if (write_fd_ == -1) {
            read_fd_ = -1;
            throw std::runtime_error("Writing to closed descriptor aborted");
        }

        ssize_t bytes_written = ::write(write_fd_, data, len);

        if (bytes_written == -1) {
            write_fd_ = -1;
            read_fd_ = -1;
            throw std::runtime_error("Write Error");
        }

        return bytes_written;
    }

    void Process::writeExact(const void *data, size_t len) {
        ssize_t bytes_written = 0;
        const char *data_start = static_cast<const char *>(data);

        while (bytes_written != len) {
            data_start += bytes_written;
            size_t bytes_written_part = write(data_start, len - bytes_written);

            if (bytes_written_part == 0) {
                write_fd_ = -1;
                read_fd_ = -1;
                throw std::runtime_error("Zero Bytes Written");
            }

            bytes_written += bytes_written_part;
        }
    }

    size_t Process::read(void *data, size_t len) {
        if (read_fd_ == -1) {
            write_fd_ = -1;
            throw std::runtime_error("Reading from closed descriptor aborted");
        }

        size_t bytes_read = ::read(read_fd_, data, len);

        if (bytes_read == -1) {
            write_fd_ = -1;
            read_fd_ = -1;
            throw std::runtime_error("Read Error");
        }

        return bytes_read;
    }

    void Process::readExact(void *data, size_t len) {
        size_t bytes_read = 0;
        char *data_start = static_cast<char *>(data);

        while (bytes_read != len) {
            data_start += bytes_read;
            size_t bytes_read_part = read(data_start, len - bytes_read);
            
            if (bytes_read_part == 0) {
                write_fd_ = -1;
                read_fd_ = -1;
                throw std::runtime_error("Zero Bytes Read");
            }

            bytes_read += bytes_read_part;
        }
    }

    void Process::closeStdin() {
        if (write_fd_ != -1) {
            close_fd({write_fd_});
            write_fd_ = -1;
        }
    }

    void Process::close() {
        if (proc_pid_) {
            if (write_fd_ != -1) {
                close_fd({write_fd_});
                write_fd_ = -1;
            }

            if (read_fd_ != -1) {
                close_fd({read_fd_});
                read_fd_ = -1;
            }

            if (::kill(proc_pid_, SIGINT) == -1) {
                throw std::runtime_error("Kill Error");
            }

            if (::waitpid(proc_pid_, nullptr, 0) == -1) {
                throw std::runtime_error("Waitpid Error");
            }

            proc_pid_ = 0;
        }
    }

    void Process::close_fd(std::vector<int> fd_for_close) {
        for (auto i : fd_for_close) {
            if (::close(i) == -1) {
                throw std::runtime_error("Close Error");
            }
        }
    }

}
