#pragma once

#include <memory>
#include <string>

enum class LogLevel {
    Info,
    Error
};

class Logger {
public:
    virtual ~Logger() = default;
    virtual void log(LogLevel level, const std::string& message) const = 0;
};

class ConsoleLogger : public Logger {
public:
    explicit ConsoleLogger(const std::string& log_file);
    void log(LogLevel level, const std::string& message) const override;

private:
    std::string log_file_;
};
