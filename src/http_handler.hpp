#pragma once

#include <memory>
#include <string>

#include "registration_service.hpp"

struct HttpResponse {
    int status_code;
    std::string body;
    std::string content_type = "application/json";
};

class HttpRequestHandler {
public:
    explicit HttpRequestHandler(std::shared_ptr<RegistrationService> service);
    HttpResponse handle(const std::string& request_body) const;

private:
    std::shared_ptr<RegistrationService> service_;
};
