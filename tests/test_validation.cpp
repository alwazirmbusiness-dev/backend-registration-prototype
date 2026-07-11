#include <cassert>
#include <iostream>
#include <memory>
#include <string>

#include "../src/http_handler.hpp"
#include "../src/logger.hpp"
#include "../src/password_hasher.hpp"
#include "../src/registration_logic.hpp"
#include "../src/registration_service.hpp"
#include "../src/user_repository.hpp"
#include "../src/uuid_generator.hpp"

namespace {

void print_case(const std::string& label, bool is_success, int status_code, const std::string& code, const std::string& message) {
    std::cout << label << " -> HTTP " << status_code << " | success=" << (is_success ? "true" : "false")
              << " | code=" << code << " | " << message << std::endl;
}

}  // namespace

int main() {
    auto logger = std::make_shared<ConsoleLogger>("");
    auto validator = std::make_shared<RegistrationValidator>();
    auto repository = std::make_shared<InMemoryUserRepository>();
    auto hasher = std::make_shared<PasswordHasher>();
    auto uuid_generator = std::make_shared<UuidGenerator>();
    auto service = std::make_shared<RegistrationService>(repository, hasher, uuid_generator, logger, validator);
    auto handler = std::make_shared<HttpRequestHandler>(service);

    RegistrationInput valid;
    valid.username = "ivan_petrov";
    valid.email = "ivan@example.com";
    valid.phone = "+79001234567";
    valid.password = "SecurePass1";
    valid.role = "individual";

    auto valid_result = service->register_user(valid);
    assert(valid_result.success);
    print_case("success", true, 200, valid_result.code, valid_result.message);

    RegistrationInput duplicate_email;
    duplicate_email.username = "new_user";
    duplicate_email.email = "ivan@example.com";
    duplicate_email.phone = "+79001234567";
    duplicate_email.password = "SecurePass1";
    duplicate_email.role = "individual";

    auto duplicate_email_result = service->register_user(duplicate_email);
    assert(!duplicate_email_result.success);
    assert(duplicate_email_result.code == "registration_failed");
    print_case("duplicate_email", false, 400, duplicate_email_result.code, duplicate_email_result.message);

    RegistrationInput duplicate_username;
    duplicate_username.username = "ivan_petrov";
    duplicate_username.email = "another@example.com";
    duplicate_username.phone = "+79001234567";
    duplicate_username.password = "SecurePass1";
    duplicate_username.role = "individual";

    auto duplicate_username_result = service->register_user(duplicate_username);
    assert(!duplicate_username_result.success);
    assert(duplicate_username_result.code == "registration_failed");
    print_case("duplicate_username", false, 400, duplicate_username_result.code, duplicate_username_result.message);

    RegistrationInput forbidden;
    forbidden.username = "admin_user";
    forbidden.email = "admin@example.com";
    forbidden.phone = "+79001234567";
    forbidden.password = "SecurePass1";
    forbidden.role = "admin";

    auto forbidden_result = service->register_user(forbidden);
    assert(!forbidden_result.success);
    assert(forbidden_result.code == "registration_forbidden");
    print_case("forbidden_role_admin", false, 403, forbidden_result.code, forbidden_result.message);

    RegistrationInput metadata_too_large;
    metadata_too_large.username = "metadata_user";
    metadata_too_large.email = "meta@example.com";
    metadata_too_large.phone = "+79001234567";
    metadata_too_large.password = "SecurePass1";
    metadata_too_large.role = "individual";
    metadata_too_large.metadata["note"] = std::string(5000, 'x');
    auto metadata_result = service->register_user(metadata_too_large);
    assert(!metadata_result.success);

    std::string request_body = R"({"username":"json_user","email":"json@example.com","phone":"+79001234567","password":"SecurePass1","role":"individual"})";
    auto response = handler->handle(request_body);
    assert(response.status_code == 200);

    std::cout << "тесты валидации прошли" << std::endl;
    return 0;
}
