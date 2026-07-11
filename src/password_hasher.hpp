#pragma once

#include <string>

class PasswordHasher {
public:
    std::string hash(const std::string& password) const;
};
