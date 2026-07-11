#pragma once

#include <string>

class AppConfig {
public:
    AppConfig();

    int server_port() const;
    std::string log_file() const;

private:
    int server_port_;
    std::string log_file_;
};
