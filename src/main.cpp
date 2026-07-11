#include <memory>
#include <iostream>

#include "config.hpp"
#include "http_handler.hpp"
#include "http_server.hpp"
#include "logger.hpp"
#include "password_hasher.hpp"
#include "registration_service.hpp"
#include "user_repository.hpp"
#include "uuid_generator.hpp"

int main() {
    AppConfig config;
    auto logger = std::make_shared<ConsoleLogger>(config.log_file());
    auto validator = std::make_shared<RegistrationValidator>();
    auto repository = std::make_shared<InMemoryUserRepository>();
    auto hasher = std::make_shared<PasswordHasher>();
    auto uuid_generator = std::make_shared<UuidGenerator>();
    auto service = std::make_shared<RegistrationService>(repository, hasher, uuid_generator, logger, validator);
    auto handler = std::make_shared<HttpRequestHandler>(service);

    logger->log(LogLevel::Info, "auth_service starting");
    HttpServer server(config.server_port(), handler, logger);
    server.run();
    return 0;
}
