#pragma once

#include <optional>

#include "user.h"

class UsersList {
   private:
    User* users;
    int capacity;
    int users_count;

   public:
    UsersList();
    UsersList(int);
    UsersList(const UsersList&) = delete;
    UsersList& operator=(const UsersList&) = delete;

    void add_user(const User&);
    int get_users_count();
    std::optional<User> search_users(const User&);

    ~UsersList();
};