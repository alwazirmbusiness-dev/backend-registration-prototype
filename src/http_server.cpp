#include "http_server.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "httplib.h"

HttpServer::HttpServer(int port, std::shared_ptr<HttpRequestHandler> handler, std::shared_ptr<Logger> logger)
    : port_(port), handler_(std::move(handler)), logger_(std::move(logger)) {}

void HttpServer::run() const {
    httplib::Server server;
    server.Post("/register", [this](const httplib::Request& req, httplib::Response& res) {
        auto response = handler_->handle(req.body);
        res.status = response.status_code;
        res.set_content(response.body, response.content_type);
    });

    logger_->log(LogLevel::Info, "http server started on port " + std::to_string(port_));
    server.listen("0.0.0.0", port_);
}
