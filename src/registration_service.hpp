#pragma once

#include <memory>
#include <string>

#include "registration_logic.hpp"

struct RegistrationOutcome {
    bool success;
    int status_code;
    std::string code;
    std::string message;
    std::string user_id;
    std::string username;
    std::string email;
    std::string role;
};

class UserRepository;
class PasswordHasher;
class UuidGenerator;
class Logger;

class RegistrationService {
public:
    RegistrationService(std::shared_ptr<UserRepository> repository,
                        std::shared_ptr<PasswordHasher> hasher,
                        std::shared_ptr<UuidGenerator> uuid_generator,
                        std::shared_ptr<Logger> logger,
                        std::shared_ptr<RegistrationValidator> validator);

    RegistrationOutcome register_user(const RegistrationInput& input) const;

private:
    std::shared_ptr<UserRepository> repository_;
    std::shared_ptr<PasswordHasher> hasher_;
    std::shared_ptr<UuidGenerator> uuid_generator_;
    std::shared_ptr<Logger> logger_;
    std::shared_ptr<RegistrationValidator> validator_;
};
