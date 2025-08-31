#include <unistd.h>

#include <iostream>
#include <string>

// User defined Header files
#include "menu.h"
#include "print_banner.h"
#include "print_message.h"
#include "user.h"
#include "users_list.h"
// #include "utilites.h"

int main() {
    UsersList u_list(20);

    // Create a test user
    User u1;
    u1.set_username("Mohamed");
    u1.set_userpasswd("12345");
    u1.deposit(2000);

    u_list.add_user(u1);

    // Shared menu state
    MenuState state;

    MenuManager my_manager(state, &u_list);

    printBanner("Welcome To Smart Wallet");

    my_manager.run_menu();

    return 0;
}
