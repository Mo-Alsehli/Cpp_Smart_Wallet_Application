#include "user.h"

#include "print_message.h"

int User::user_count = 0;

User::User() {
    user_name = "";
    user_passwd = "";
    balance = 0;
    user_count++;
    id = user_count;
}

void User::set_username(std::string user_name) { this->user_name = user_name; }

std::string User::get_username() { return this->user_name; }

void User::set_userpasswd(std::string user_passwd) { this->user_passwd = user_passwd; }

std::string User::get_userpasswd() { return this->user_passwd; }

bool User::operator==(const User& u) const {
    if (this->user_name != u.user_name || this->user_passwd != u.user_passwd) return false;

    return true;
}

int User::deposit(int value) {
    balance += value;
    return balance;
}

int User::withdraw(int value) {
    if (value > balance) {
        printMessage("Insufficient Balance", MsgType::ERROR);
        return 0;
    }
    balance -= value;
    printMessage("Withdraw successfull", MsgType::INFO);

    return balance;
}

int User::get_balance() { return balance; }