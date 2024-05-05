#ifndef MENU_H
#define MENU_H

#include <vector>
#include <functional>
#include "OtherFunctions.h"

class Menu
{
private:
    std::vector<std::pair<std::string, std::function<void()>>> MenuOptions;
    std::string title;
public:
    Menu(std::string menuTitle) : title(menuTitle) {};
    void f_addMenuOption(std::string actionTitle, std::function<void()> action);
    
    void f_displayMenu();
    
    void f_chooseOption();
};

#endif