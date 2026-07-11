#pragma once

#include <string>

#include "registration_logic.hpp"

class JsonParser {
public:
    RegistrationInput parse(const std::string& body) const;
};
