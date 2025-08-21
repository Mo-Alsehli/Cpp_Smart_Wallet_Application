#include <unistd.h>

#include <iostream>
#include <string>

// User defined Header files
#include "menu.h"
#include "print_banner.h"
#include "print_message.h"
#include "user.h"
#include "users_list.h"
#include "utilites.h"

// extern User database[20];
// extern int users_count;
UsersList u_list(20);
// AppState curr_state;

int main() {
    // Create user
    User u1;
    u1.set_username("Mohamed");
    u1.set_userpasswd("12345");
    u1.deposit(2000);

    u_list.add_user(u1);
    LoginMenu login_menu(u_list);
    MenuManager my_manager(&login_menu);

    printBanner("Welcome To Smart Wallet");
    std::string query;

    while (true) {
        printMessage("Login Page", MsgType::INFO);
        std::cout << "Please Make a Selection: \n";
        std::cout << "(L) Login\n";
        std::cout << "(Q) Quit\n";
        std::cin >> query;
        if (query[0] == 'L' || query[0] == 'l') {
            MenuState state = my_manager.run_menu();
            if (state.running) {
                User u = *state.curr_user;

                menu_page(u);
            }
            // Menu.
        } else if (query[0] == 'q' || query[0] == 'Q') {
            printMessage("Goodbye!", MsgType::INFO);
            break;
        }
    }

    return 0;
}