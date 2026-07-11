#include "json_parser.hpp"

#include <nlohmann/json.hpp>

RegistrationInput JsonParser::parse(const std::string& body) const {
    RegistrationInput input;
    if (body.empty()) {
        return input;
    }

    try {
        const auto json = nlohmann::json::parse(body);
        if (json.contains("username") && json["username"].is_string()) {
            input.username = json["username"].get<std::string>();
        }
        if (json.contains("email") && json["email"].is_string()) {
            input.email = json["email"].get<std::string>();
        }
        if (json.contains("phone") && json["phone"].is_string()) {
            input.phone = json["phone"].get<std::string>();
        }
        if (json.contains("password") && json["password"].is_string()) {
            input.password = json["password"].get<std::string>();
        }
        if (json.contains("role") && json["role"].is_string()) {
            input.role = json["role"].get<std::string>();
        }
    } catch (const std::exception&) {
        return input;
    }

    return input;
}
