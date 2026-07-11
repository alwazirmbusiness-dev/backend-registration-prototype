#include "logger.hpp"

#include <fstream>
#include <iostream>

ConsoleLogger::ConsoleLogger(const std::string& log_file) : log_file_(log_file) {}

void ConsoleLogger::log(LogLevel level, const std::string& message) const {
    std::ofstream out(log_file_, std::ios::app);
    if (out.is_open()) {
        out << (level == LogLevel::Info ? "INFO" : "ERROR") << ": " << message << "\n";
    }
    std::cout << message << std::endl;
}
