#include "Menu.h"

void Menu::f_addMenuOption(std::string actionTitle, std::function<void()> action)
{
    MenuOptions.push_back({ actionTitle, action });
}
void Menu::f_displayMenu()
{
    system("cls");
    std::cout << title << std::endl;
    for (size_t i = 0; i < MenuOptions.size(); ++i)
    {
        std::cout << i << ". " << MenuOptions[i].first << std::endl;
    }
}
void Menu::f_chooseOption()
{
    int option;
    std::cout << "Wybor: ";
    option = f_limitedInputNumber(0, MenuOptions.size() - 1);
    MenuOptions[option].second();
}