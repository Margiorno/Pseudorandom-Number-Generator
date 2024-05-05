#include "OtherFunctions.h"

int f_limitedInputNumber(int min, int max)
{
    int input;
    std::cin >> input;
    if (std::cin.fail() || (input > max) || (input < min)) {
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cout << "Niepoprawna wartosc. Prosze podac nowa: ";
        return f_limitedInputNumber(min, max);
    }
    return input;
}

void f_checkFileName(std::string& filename)
{
    if (filename.length() < 4 || filename.substr(filename.length() - 4) != ".txt")
    {
        filename += ".txt";
    }
}