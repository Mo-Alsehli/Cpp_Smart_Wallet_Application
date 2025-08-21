#pragma once

#include <iostream>
#include <string>

class User {
   private:
    std::string user_name;
    std::string user_passwd;
    float balance;
    int id;

   public:
    static int user_count;
    User();
    //~User();

    void set_username(std::string user_name);

    std::string get_username();

    void set_userpasswd(std::string user_passwd);

    std::string get_userpasswd();

    bool operator==(const User&) const;

    int deposit(int value);

    int withdraw(int value);

    int get_balance();
};