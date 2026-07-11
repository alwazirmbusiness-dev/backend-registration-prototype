#include "uuid_generator.hpp"

#include <chrono>
#include <sstream>

std::string UuidGenerator::generate() const {
    static unsigned long long counter = 0;
    auto now = std::chrono::steady_clock::now().time_since_epoch().count();
    std::ostringstream oss;
    oss << "uuid-" << now << "-" << ++counter;
    return oss.str();
}
