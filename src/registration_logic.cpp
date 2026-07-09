#include "registration_logic.hpp"

#include <algorithm>
#include <cctype>
#include <regex>

namespace {

bool is_valid_email(const std::string& value) {
    static const std::regex pattern(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    return std::regex_match(value, pattern);
}

bool is_valid_phone(const std::string& value) {
    return !value.empty() && value.size() <= 32 && value[0] == '+';
}

bool contains_upper(const std::string& value) {
    return std::any_of(value.begin(), value.end(), [](unsigned char c) { return std::isupper(c) != 0; });
}

bool contains_lower(const std::string& value) {
    return std::any_of(value.begin(), value.end(), [](unsigned char c) { return std::islower(c) != 0; });
}

bool contains_digit(const std::string& value) {
    return std::any_of(value.begin(), value.end(), [](unsigned char c) { return std::isdigit(c) != 0; });
}

bool is_valid_password(const std::string& value) {
    return value.size() >= 8 && value.size() <= 20 && contains_upper(value) && contains_lower(value) && contains_digit(value);
}

bool is_valid_role(const std::string& value) {
    return value == "individual" || value == "logistics_partner" || value == "business_account";
}

bool is_valid_inn(const std::string& value) {
    if (value.empty()) return true;
    if (value.size() != 10 && value.size() != 12) return false;
    return std::all_of(value.begin(), value.end(), [](unsigned char c) { return std::isdigit(c) != 0; });
}

}  // namespace

ValidationResult validate_registration(const RegistrationInput& input) {
    if (input.username.empty() || input.username.size() > 64) {
        return {false, "validation_error", "Имя пользователя должно быть от 1 до 64 символов"};
    }

    if (input.email.empty() || input.email.size() > 255 || !is_valid_email(input.email)) {
        return {false, "validation_error", "Email должен быть валидным адресом"};
    }

    if (input.phone.empty() || input.phone.size() > 32 || !is_valid_phone(input.phone)) {
        return {false, "validation_error", "Телефон обязателен и не должен превышать 32 символа"};
    }

    if (!is_valid_password(input.password)) {
        return {false, "validation_error", "Пароль должен быть от 8 до 20 символов и содержать заглавную, строчную букву и цифру"};
    }

    if (!input.role.empty() && !is_valid_role(input.role)) {
        return {false, "registration_forbidden", "Роль запрещена"};
    }

    if (input.role == "business_account" && input.company_name.empty()) {
        return {false, "validation_error", "Для роли business_account обязательно указать company_name"};
    }

    if (!input.company_name.empty() && input.company_name.size() > 256) {
        return {false, "validation_error", "company_name не должен превышать 256 символов"};
    }

    if (!is_valid_inn(input.inn)) {
        return {false, "validation_error", "ИНН должен содержать 10 или 12 цифр"};
    }

    return {true, "", ""};
}
