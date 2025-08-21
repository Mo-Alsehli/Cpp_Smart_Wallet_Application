#pragma once

#include <memory>
#include <optional>

#include "print_banner.h"
#include "print_message.h"
#include "user.h"
#include "users_list.h"

struct MenuState {
    std::optional<User> curr_user;
    bool running = true;
};

// enum MenuStatus { MENU_ERROR, MENU_OK };

class Menu {
   public:
    virtual MenuState display() = 0;
};

class MenuManager {
   private:
    Menu* menu_type = nullptr;

   public:
    MenuManager(Menu*);

    void set_menu(Menu* menu);

    MenuState run_menu();
};

class LoginMenu : public Menu {
   private:
    UsersList& curr_list;
    MenuState state;

   public:
    LoginMenu(UsersList& u_list);
    MenuState display() override;
};

class BoardMenu : public Menu {
   public:
    MenuState display() override;
};

class ConfirmationMenu : public Menu {
   public:
    MenuState display() override;
};