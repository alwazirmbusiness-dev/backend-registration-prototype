cmake_minimum_required(VERSION 3.16)
project(auth_service LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(auth_service
    src/main.cpp
    src/registration_logic.cpp
    src/http_handler.cpp
)

target_include_directories(auth_service PRIVATE src)
target_compile_options(auth_service PRIVATE -Wall -Wextra -Wpedantic)
