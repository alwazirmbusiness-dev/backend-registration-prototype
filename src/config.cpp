#include "config.hpp"

#include <cstdlib>

AppConfig::AppConfig() {
    const char* port = std::getenv("SERVER_PORT");
    server_port_ = port ? std::atoi(port) : 8080;
    const char* log_file = std::getenv("LOG_FILE");
    log_file_ = log_file ? log_file : "auth_service.log";
}

int AppConfig::server_port() const { return server_port_; }
std::string AppConfig::log_file() const { return log_file_; }
