#pragma once

#include <string>
#include <unordered_map>

struct RegistrationInput {
    std::string username;
    std::string email;
    std::string phone;
    std::string password;
    std::string role = "individual";
    std::string company_name;
    std::string inn;
    std::unordered_map<std::string, std::string> metadata;
};

struct ValidationResult {
    bool is_valid;
    std::string error_code;
    std::string message;
};

class RegistrationValidator {
public:
    ValidationResult validate(const RegistrationInput& input) const;
};

ValidationResult validate_registration(const RegistrationInput& input);
