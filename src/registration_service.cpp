#include "registration_service.hpp"

#include <utility>

#include "logger.hpp"
#include "password_hasher.hpp"
#include "user_repository.hpp"
#include "uuid_generator.hpp"

RegistrationService::RegistrationService(std::shared_ptr<UserRepository> repository,
                                           std::shared_ptr<PasswordHasher> hasher,
                                           std::shared_ptr<UuidGenerator> uuid_generator,
                                           std::shared_ptr<Logger> logger,
                                           std::shared_ptr<RegistrationValidator> validator)
    : repository_(std::move(repository)),
      hasher_(std::move(hasher)),
      uuid_generator_(std::move(uuid_generator)),
      logger_(std::move(logger)),
      validator_(std::move(validator)) {}

RegistrationOutcome RegistrationService::register_user(const RegistrationInput& input) const {
    auto validation = validator_ ? validator_->validate(input) : ValidationResult{false, "validation_error", "validation failed"};
    if (!validator_ || !validation.is_valid) {
        logger_->log(LogLevel::Error, validation.message);
        return {false, validation.error_code == "registration_forbidden" ? 403 : 400, validation.error_code, validation.message, "", input.username, input.email, input.role};
    }

    if (repository_->user_exists_by_email(input.email)) {
        logger_->log(LogLevel::Error, "duplicate email");
        return {false, 400, "registration_failed", "Пользователь с таким email уже существует", "", input.username, input.email, input.role};
    }

    if (repository_->user_exists_by_username(input.username)) {
        logger_->log(LogLevel::Error, "duplicate username");
        return {false, 400, "registration_failed", "Пользователь с таким username уже существует", "", input.username, input.email, input.role};
    }

    auto hashed_password = hasher_->hash(input.password);
    auto id = uuid_generator_->generate();
    repository_->save_user(input.username, input.email, hashed_password, input.role, id);

    logger_->log(LogLevel::Info, "user registered");
    return {true, 200, "success", "Пользователь успешно зарегистрирован", id, input.username, input.email, input.role};
}
