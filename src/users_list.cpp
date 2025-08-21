#include "users_list.h"

#include "print_message.h"

UsersList::UsersList() {
    capacity = 0;
    users = nullptr;
    users_count = 0;
}

UsersList::UsersList(int capacity) {
    this->capacity = capacity;
    this->users = new User[capacity];
    this->users_count = 0;
}

void UsersList::add_user(const User& u) {
    if (users_count < capacity && users != nullptr) {
        users[users_count++] = u;
    } else {
        printMessage("Users Database is Full", MsgType::ERROR);
    }
}

int UsersList::get_users_count() { return users_count; }

std::optional<User> UsersList::search_users(const User& u) {
    for (int i = 0; i < users_count; i++) {
        if (u == users[i]) {
            return users[i];
        }
    }

    return std::nullopt;
}

UsersList::~UsersList() { delete[] users; }