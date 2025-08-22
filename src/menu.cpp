#include "menu.h"

#include <iostream>

// MenuManager
MenuManager::MenuManager(MenuState& state, UsersList* u_list) : state_ref(state), curr_users(u_list) {
    menu_type = new LoginMenu(*curr_users, *this);
};

void MenuManager::set_menu(Menu* menu) {
    delete menu_type;
    menu_type = menu;
}

MenuReturnState MenuManager::run_menu() {
    MenuReturnState state = MenuReturnState::Continue;
    while (state == MenuReturnState::Continue) {
        state = menu_type->display(state_ref);
    }
    return state;
}

// LoginMenu
LoginMenu::LoginMenu(UsersList& u_list, MenuManager& manager) : curr_list(u_list), m_manager(manager){};

MenuReturnState LoginMenu::display(MenuState& state) {
    std::string user_name;
    std::string user_passwd;
    std::string query;

    printMessage("Login Page", MsgType::INFO);
    std::cout << "Please Make a Selection: \n";
    std::cout << "(L) Login\n";
    std::cout << "(Q) Quit\n";
    std::cin >> query;

    if (query[0] == 'L' || query[0] == 'l') {
        std::cout << "\033[2J\033[1;1H";  // This is to clear the screen
        //  system("clear");
        printMessage("Login Page::Enter Login Credentials", MsgType::INFO);
        std::cout << "Please enter user name: ";
        std::cin >> user_name;
        std::cout << "Enter Password: ";
        std::cin >> user_passwd;

        User user;
        user.set_username(user_name);
        user.set_userpasswd(user_passwd);
        auto result = curr_list.search_users(user);
        if (result) {
            state.curr_user = *result;
            std::cout << "\033[2J\033[1;1H";  // This is to clear the screen
            std::string message = "Welcome " + state.curr_user->get_username();
            printBanner(message);
            state.running = true;
            m_manager.set_menu(new UserMenu(m_manager));
            return MenuReturnState::Continue;
        } else {
            printMessage("Invalid username or password.", MsgType::ERROR);
            std::cout << "[R]etry or [Q]uit? ";
            std::string choice;
            std::cin >> choice;

            if (!choice.empty() && (choice[0] == 'q' || choice[0] == 'Q')) {
                printMessage("Login cancelled.", MsgType::WARNING);
                state.running = false;
                state.curr_user.reset();
                return MenuReturnState::Exit;
            }
        }
    } else if (query[0] == 'q' || query[0] == 'Q') {
        printMessage("Goodbye!", MsgType::INFO);
        return MenuReturnState::ERROR;
    } else {
        printMessage("Invalid selection. Please try again.", MsgType::WARNING);
        return MenuReturnState::Continue;
    }
}

UserMenu::UserMenu(MenuManager& manager) : m_manager(manager){};

MenuReturnState UserMenu::display(MenuState& state) {
    state.running = true;  // Mark the menu session as active

    // Ensure we have a valid logged-in user
    if (!state.curr_user.has_value()) {
        printMessage("No user is currently logged in.", MsgType::ERROR);
        state.running = false;
        return MenuReturnState::ERROR;
    }

    // Get reference to current user from shared MenuState
    User& user = *state.curr_user;

    // Display menu options
    std::cout << "Please Make a Selection\n";
    std::cout << "[1] View balance\n";
    std::cout << "[2] Withdraw\n";
    std::cout << "[3] Deposit\n";
    std::cout << "[4] Logout\n";

    std::string query;
    std::cin >> query;  // Get user input

    if (query == "1") {
        // Option 1: View balance
        float balance = user.get_balance();
        printMessage("Your Balance: " + std::to_string(balance), MsgType::INFO);
        return MenuReturnState::Continue;
    } else if (query == "2") {
        // Option 2: Withdraw
        double value;
        std::cout << "Enter a value to withdraw: ";
        std::cin >> value;
        if (value > 0) {
            user.withdraw(value);  // Withdraw from user's balance
        } else {
            printMessage("Invalid Value", MsgType::ERROR);
        }
        return MenuReturnState::Continue;

    } else if (query == "3") {
        // Option 3: Deposit
        double value;
        std::cout << "Enter a value to deposit: ";
        std::cin >> value;
        if (value > 0) {
            user.deposit(value);
            printMessage("Deposited Successfully\nYour new balance: " + std::to_string(user.get_balance()), MsgType::INFO);
        } else {
            printMessage("Invalid Value", MsgType::ERROR);
        }
        return MenuReturnState::Continue;

    } else if (query == "4") {
        // Option 4: Logout
        printMessage("Logged Out", MsgType::INFO);
        m_manager.set_menu(new LoginMenu(*m_manager.curr_users, m_manager));
        return MenuReturnState::Continue;

    } else {
        // Catch-all for invalid input
        printMessage("Invalid selection", MsgType::WARNING);
        return MenuReturnState::Continue;
    }
}
