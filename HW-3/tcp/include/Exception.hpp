#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <string>
#include <exception>
#include <stdexcept>

namespace tcp {

    class DescriptorError : public std::runtime_error {
    public:
        explicit DescriptorError(const std::string& err);
    };

    class ConnectionError : public std::runtime_error {
    public:
        explicit ConnectionError(const std::string& err);
    };

    class ServerError : public std::runtime_error {
    public:
        explicit ServerError(const std::string& err);
    };

}

#endif
