#include <cstdlib>
#include <iostream>
#include <string>

#include "registration_logic.hpp"

int main() {
    std::cout << "auth_service starting" << std::endl;

    RegistrationInput input;
    input.username = "ivan_petrov";
    input.email = "ivan@example.com";
    input.phone = "+79001234567";
    input.password = "SecurePass1";
    input.role = "individual";

    auto result = validate_registration(input);
    if (!result.is_valid) {
        std::cerr << "validation failed: " << result.error_code << " - " << result.message << std::endl;
        return 1;
    }

    std::cout << "registration input validated successfully" << std::endl;
    return 0;
}
