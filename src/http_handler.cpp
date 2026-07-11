#include "http_handler.hpp"

#include <sstream>
#include <utility>

#include "json_parser.hpp"

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

HttpRequestHandler::HttpRequestHandler(std::shared_ptr<RegistrationService> service) : service_(std::move(service)) {}

HttpResponse HttpRequestHandler::handle(const std::string& request_body) const {
    JsonParser parser;
    RegistrationInput input = parser.parse(request_body);

    auto result = service_->register_user(input);
    std::ostringstream oss;
    oss << "{\"success\":" << (result.success ? "true" : "false")
        << ",\"code\":\"" << json_escape(result.code) << "\""
        << ",\"message\":\"" << json_escape(result.message) << "\"";
    if (result.success && !result.user_id.empty()) {
        oss << ",\"user\":{\"id\":\"" << json_escape(result.user_id)
            << "\",\"username\":\"" << json_escape(result.username)
            << "\",\"email\":\"" << json_escape(result.email)
            << "\",\"role\":\"" << json_escape(result.role) << "\"}";
    }
    oss << "}";

    return {result.status_code, oss.str()};
}
