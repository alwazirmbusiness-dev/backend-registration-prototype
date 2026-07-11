#pragma once

#include <memory>
#include <string>

#include "http_handler.hpp"
#include "logger.hpp"

class HttpServer {
public:
    HttpServer(int port, std::shared_ptr<HttpRequestHandler> handler, std::shared_ptr<Logger> logger);
    void run() const;

private:
    int port_;
    std::shared_ptr<HttpRequestHandler> handler_;
    std::shared_ptr<Logger> logger_;
};
