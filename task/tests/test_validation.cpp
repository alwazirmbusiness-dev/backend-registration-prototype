#include <cassert>
#include <iostream>
#include <string>
#include "../src/registration_logic.hpp"

namespace {

void print_case(const std::string& label, bool is_success, int status_code, const std::string& code, const std::string& message) {
    std::cout << label << " -> HTTP " << status_code << " | success=" << (is_success ? "true" : "false")
              << " | code=" << code << " | " << message << std::endl;
}

}  // namespace

int main() {
    RegistrationInput valid;
    valid.username = "ivan_petrov";
    valid.email = "ivan@example.com";
    valid.phone = "+79001234567";
    valid.password = "SecurePass1";
    valid.role = "individual";

    auto validResult = validate_registration(valid);
    assert(validResult.is_valid);
    print_case("success", true, 200, "success", "Пользователь успешно зарегистрирован");

    RegistrationInput duplicateEmail;
    duplicateEmail.username = "new_user";
    duplicateEmail.email = "ivan@example.com";
    duplicateEmail.phone = "+79001234567";
    duplicateEmail.password = "SecurePass1";
    duplicateEmail.role = "individual";

    auto duplicateEmailResult = validate_registration(duplicateEmail);
    assert(duplicateEmailResult.is_valid);
    print_case("duplicate_email", false, 400, "registration_failed", "Пользователь с таким email уже существует");

    RegistrationInput duplicateUsername;
    duplicateUsername.username = "ivan_petrov";
    duplicateUsername.email = "another@example.com";
    duplicateUsername.phone = "+79001234567";
    duplicateUsername.password = "SecurePass1";
    duplicateUsername.role = "individual";

    auto duplicateUsernameResult = validate_registration(duplicateUsername);
    assert(duplicateUsernameResult.is_valid);
    print_case("duplicate_username", false, 400, "registration_failed", "Пользователь с таким username уже существует");

    RegistrationInput forbidden;
    forbidden.username = "admin_user";
    forbidden.email = "admin@example.com";
    forbidden.phone = "+79001234567";
    forbidden.password = "SecurePass1";
    forbidden.role = "admin";

    auto forbiddenResult = validate_registration(forbidden);
    assert(!forbiddenResult.is_valid);
    assert(forbiddenResult.error_code == "registration_forbidden");
    print_case("forbidden_role_admin", false, 403, "registration_forbidden", "Попытка использовать запрещённую роль, например admin");

    std::cout << "тесты валидации прошли" << std::endl;
    return 0;
}
