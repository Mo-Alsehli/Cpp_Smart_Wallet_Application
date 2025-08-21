#include "menu.h"

// Menu Manager.
MenuManager::MenuManager(Menu* menu) { menu_type = menu; }

void MenuManager::set_menu(Menu* menu) { menu_type = menu; }

MenuState MenuManager::run_menu() {
    if (menu_type) return menu_type->display();
}

// Login Menu.

LoginMenu::LoginMenu(UsersList& u_list) { curr_list = u_list; }

MenuState LoginMenu::display() {
    MenuState out;
    while (1) {
        std::string user_name;
        std::string user_passwd;
        printMessage("Login Page", MsgType::INFO);
        std::cout << "Please enter user name: ";
        std::cin >> user_name;
        std::cout << "Enter Password: ";
        std::cin >> user_passwd;

        User user;
        user.set_username(user_name);
        user.set_userpasswd(user_passwd);
        auto result = curr_list.search_users(user);
        if (result) {
            out.curr_user = result;
            std::cout << "Logged User Balance: " << out.curr_user->get_balance() << std::endl;
            std::string message = "Welcome " + out.curr_user->get_username();
            printBanner(message);
            out.running = true;
            return out;
        } else {
            printMessage("Invalid username or password.", MsgType::ERROR);
            std::cout << "[R]etry or [Q]uit? ";
            std::string choice;
            std::cin >> choice;

            if (!choice.empty() && (choice[0] == 'q' || choice[0] == 'Q')) {
                printMessage("Login cancelled.", MsgType::WARNING);
                state.running = false;
                return out;
            }
        }
    }
}