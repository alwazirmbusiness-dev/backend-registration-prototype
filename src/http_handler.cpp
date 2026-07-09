#include "http_handler.hpp"

#include <iostream>
#include <sstream>

namespace {

std::string json_escape(const std::string& value) {
    std::ostringstream oss;
    for (char ch : value) {
        switch (ch) {
            case '"': oss << "\\\""; break;
            case '\\': oss << "\\\\"; break;
            case '\n': oss << "\\n"; break;
            case '\r': oss << "\\r"; break;
            case '\t': oss << "\\t"; break;
            default: oss << ch; break;
        }
    }
    return oss.str();
}

}  // namespace

HttpResponse handle_register(const std::string& request_body) {
    (void)request_body;
    RegistrationInput input;
    input.username = "ivan_petrov";
    input.email = "ivan@example.com";
    input.phone = "+79001234567";
    input.password = "SecurePass1";
    input.role = "individual";

    auto validation = validate_registration(input);
    if (!validation.is_valid) {
        std::ostringstream oss;
        oss << "{\"success\":false,\"error\":{\"code\":\"" << validation.error_code << "\",\"message\":\"" << json_escape(validation.message) << "\"}}";
        return {validation.error_code == "registration_forbidden" ? 403 : 400, oss.str()};
    }

    std::ostringstream oss;
    oss << "{\"success\":true,\"message\":\"User registered successfully.\",\"user\":{\"id\":\"demo-id\",\"username\":\"" << json_escape(input.username) << "\",\"email\":\"" << json_escape(input.email) << "\",\"role\":\"" << json_escape(input.role) << "\"}}";
    return {200, oss.str()};
}
