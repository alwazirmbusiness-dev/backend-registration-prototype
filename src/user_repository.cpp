#include "user_repository.hpp"

#include <unordered_map>
#include <vector>

namespace {

struct UserRecord {
    std::string username;
    std::string email;
    std::string password_hash;
    std::string role;
    std::string id;
};

std::vector<UserRecord>& users() {
    static std::vector<UserRecord> storage;
    return storage;
}

}  // namespace

bool InMemoryUserRepository::user_exists_by_email(const std::string& email) const {
    for (const auto& user : users()) {
        if (user.email == email) {
            return true;
        }
    }
    return false;
}

bool InMemoryUserRepository::user_exists_by_username(const std::string& username) const {
    for (const auto& user : users()) {
        if (user.username == username) {
            return true;
        }
    }
    return false;
}

void InMemoryUserRepository::save_user(const std::string& username, const std::string& email, const std::string& password_hash, const std::string& role, const std::string& id) {
    users().push_back({username, email, password_hash, role, id});
}
