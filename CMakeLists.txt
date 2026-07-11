cmake_minimum_required(VERSION 3.16)
project(auth_service LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(AUTH_SERVICE_SOURCES
    src/main.cpp
    src/registration_logic.cpp
    src/http_handler.cpp
    src/http_server.cpp
    src/json_parser.cpp
    src/config.cpp
    src/logger.cpp
    src/password_hasher.cpp
    src/user_repository.cpp
    src/uuid_generator.cpp
    src/registration_service.cpp
)

add_executable(auth_service ${AUTH_SERVICE_SOURCES})
target_include_directories(auth_service PRIVATE src)
target_include_directories(auth_service PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/httplib)
target_include_directories(auth_service PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/json/include)
target_compile_options(auth_service PRIVATE -Wall -Wextra -Wpedantic)
target_compile_definitions(auth_service PRIVATE _WIN32_WINNT=0x0A00)

target_link_libraries(auth_service PRIVATE ws2_32)

add_executable(auth_service_tests
    tests/test_validation.cpp
    src/registration_logic.cpp
    src/http_handler.cpp
    src/http_server.cpp
    src/json_parser.cpp
    src/config.cpp
    src/logger.cpp
    src/password_hasher.cpp
    src/user_repository.cpp
    src/uuid_generator.cpp
    src/registration_service.cpp
)

target_include_directories(auth_service_tests PRIVATE src)
target_include_directories(auth_service_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/httplib)
target_include_directories(auth_service_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/json/include)
target_compile_options(auth_service_tests PRIVATE -Wall -Wextra -Wpedantic)
target_compile_definitions(auth_service_tests PRIVATE _WIN32_WINNT=0x0A00)

target_link_libraries(auth_service_tests PRIVATE ws2_32)
