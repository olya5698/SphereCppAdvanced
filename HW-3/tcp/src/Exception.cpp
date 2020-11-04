#include "Exception.hpp"

#include <cstring>

namespace tcp {

    DescriptorError::DescriptorError(const std::string& err)
        : std::runtime_error("DescriptorError: " + err + " --- " + strerror(errno)) {}

    ConnectionError::ConnectionError(const std::string& err)
        : std::runtime_error("ConnectionError: " + err + " --- " + strerror(errno)) {}

    ServerError::ServerError(const std::string& err)
        : std::runtime_error("ServerError: " + err + " --- " + strerror(errno)) {}

}
