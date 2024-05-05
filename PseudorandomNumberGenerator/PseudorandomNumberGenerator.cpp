#include "Generator.h"
#include "Menu.h"


int main()
{
    RandomNumberGenerator test = RandomNumberGenerator::get();

    Menu* menu1 = new Menu("Wybierz metode generowania liczb pseudolosowych");
    menu1->f_addMenuOption("Liniowa metoda kongruencyjna", [&test]() { test.f_generateRandomNumbers(); });
    menu1->f_addMenuOption("Addytywna metoda kongruencyjna", [&test]() { test.f_generateWithAdditiveCongruentMethod(); });

    Menu* menu2 = new Menu("Wybierz sposob wyswietlania wynikow");
    menu2->f_addMenuOption("Wyswietl w konsoli", [&test]() { test.f_displayGeneratedNumbers(); });
    menu2->f_addMenuOption("Zapisz w pliku tekstowym", [&test]() { test.f_saveGeneratedNumbersInFile(); });

    menu1->f_displayMenu();
    menu1->f_chooseOption();
    menu2->f_displayMenu();
    menu2->f_chooseOption();

    return 0;
}