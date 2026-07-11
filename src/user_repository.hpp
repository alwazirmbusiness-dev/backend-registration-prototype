#pragma once

#include <string>

class UserRepository {
public:
    virtual ~UserRepository() = default;
    virtual bool user_exists_by_email(const std::string& email) const = 0;
    virtual bool user_exists_by_username(const std::string& username) const = 0;
    virtual void save_user(const std::string& username, const std::string& email, const std::string& password_hash, const std::string& role, const std::string& id) = 0;
};

class InMemoryUserRepository : public UserRepository {
public:
    bool user_exists_by_email(const std::string& email) const override;
    bool user_exists_by_username(const std::string& username) const override;
    void save_user(const std::string& username, const std::string& email, const std::string& password_hash, const std::string& role, const std::string& id) override;
};
