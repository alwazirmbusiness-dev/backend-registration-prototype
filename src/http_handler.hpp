#pragma once

#include <string>

#include "registration_logic.hpp"

struct HttpResponse {
    int status_code;
    std::string body;
};

HttpResponse handle_register(const std::string& request_body);
