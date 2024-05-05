#include "Generator.h"

void RandomNumberGenerator::f_clearStack()
{
    while (!generated_numbers.empty())
    {
        generated_numbers.pop_back();
    }
}

void RandomNumberGenerator::f_fillStackWithRandomNumbers(int quantity)
{
    f_clearStack();
    generated_numbers.push_back(first_x % modulo);

    for (int i = 1; i < quantity; i++)
    {
        generated_numbers.push_back((multiplier * generated_numbers[generated_numbers.size() - 1] + adder) % modulo);
    }
}

void RandomNumberGenerator::f_getModulo()
{
    int max_value;
    std::cout << "Podaj najwieksza mozliwa wartosc: ";
    std::cin >> max_value;
    modulo = max_value + 1;
}

bool RandomNumberGenerator::f_isPrime(int number)
{
    if (number < 2)
        return false;
    for (int i = 2; i * i <= number; i++)
        if (number % i == 0)
            return false;
    return true;
}

void RandomNumberGenerator::f_getModuloPrimeNumbersDivisiers()
{
    for (int i = 2; i <= modulo; i++) {
        if (modulo % i == 0 && f_isPrime(i)) {
            moduloPrimeNumbersDivisiers.push_back(i);
        }
    }
}

int RandomNumberGenerator::f_findGreatestCommonDivisier(int a, int b)
{
    if (a == b) return a;
    return b == 0 ? a : f_findGreatestCommonDivisier(b, a % b);
}

void RandomNumberGenerator::f_getAdders()
{
    for (int i = 0; i < modulo; i++)
    {
        if (f_findGreatestCommonDivisier(modulo, i) == 1)
        {
            adders.push_back(i);
        }
    }
}

void RandomNumberGenerator::f_getMultipliers()
{
    std::vector<int> listLambdas(modulo, 0);
    int maxLambda = 0;
    for (int candinateIndex = 2; candinateIndex < modulo; candinateIndex++)
    {
        if (f_findGreatestCommonDivisier(candinateIndex, modulo) != 1)
            continue;
        int lambda = 1;
        while (lambda < modulo - 1 && long long(pow(candinateIndex, lambda)) % modulo != 1)
        {
            lambda++;
        }
        if (lambda > maxLambda)maxLambda = lambda;
        listLambdas[candinateIndex] = lambda;
    }
    for (int i = 0; i < listLambdas.size(); i++)
    {
        if (listLambdas[i] == maxLambda)
            multipliers.push_back(i);
    }

    std::reverse(multipliers.begin(), multipliers.end());
    for (int i = multipliers.size() - 1; i >= 0; i--)
    {
        if (multipliers.size() == 1)
        {
            break;
        }
        else if (!(modulo % 4) && ((multipliers[i] - 1) % 4))
        {
            multipliers.erase(multipliers.begin() + i);
            continue;
        }
        else
        {
            for (int j = 0; j < moduloPrimeNumbersDivisiers.size(); j++)
            {
                if (((multipliers[i] - 1) % moduloPrimeNumbersDivisiers[j]))
                {
                    multipliers.erase(multipliers.begin() + i);
                    break;
                }
            }
        }
    }
}

void RandomNumberGenerator::f_getSeeds()
{
    for (int start_x = 0; start_x < modulo; start_x++)
    {
        for (int i_multiplier = 0; i_multiplier < multipliers.size(); i_multiplier++)
        {
            for (int i_adder = 0; i_adder < adders.size(); i_adder++)
            {
                seeds.push_back({ start_x,multipliers[i_multiplier],adders[i_adder] });
            }
        }
    }
}

void RandomNumberGenerator::f_setSeed()
{
    int seed = std::time(0) % seeds.size();
    first_x = seeds[seed][0];
    multiplier = seeds[seed][1];
    adder = seeds[seed][2];
}

RandomNumberGenerator& RandomNumberGenerator::get()
{
    return generator;
}

void RandomNumberGenerator::f_generateRandomNumbers()
{
    int quantity;
    f_getModulo();
    f_getModuloPrimeNumbersDivisiers();
    f_getAdders();
    f_getMultipliers();
    f_getSeeds();
    std::cout << "Podaj ilosc cyfr do wygenerowania: ";
    std::cin >> quantity;
    f_setSeed();
    f_fillStackWithRandomNumbers(quantity);
}

void RandomNumberGenerator::f_displayGeneratedNumbers() {
    for (int i = 0; i < generated_numbers.size(); i++)
    {
        std::cout << generated_numbers[i] << std::endl;
    }
}

void RandomNumberGenerator::f_saveGeneratedNumbersInFile()
{
    std::string filename;
    std::cout << "Podaj nazwe pliku do zapisu: ";
    std::cin >> filename;
    f_checkFileName(filename);
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Ziarno:\n" << "x poczatkowy: " << first_x << "  mnoznik: " << multiplier << "  Przyrost: " << adder;
        for (int element : generated_numbers) {
            file << std::endl << element;
        }
        file.close();
    }
    else {
        std::cerr << "Nie udalo sie otworzyc pliku: " << std::endl;
    }
}

void RandomNumberGenerator::f_generateWithAdditiveCongruentMethod()
{
    f_generateRandomNumbers();
    int j, k;
    std::cout << "Podaj wspolczynnik j: ";
    j = f_limitedInputNumber(0, generated_numbers.size() - 1);
    std::cout << "Podaj wspolczynnik k: ";
    k = f_limitedInputNumber(0, generated_numbers.size() - 1);
    std::reverse(generated_numbers.begin(), generated_numbers.end());
    for (int i = 0; i < generated_numbers.size(); i++)
    {
        generated_numbers[k] = (generated_numbers[k] + generated_numbers[j]) % modulo;
        if (j == 0)
            j = generated_numbers.size();
        if (k == 0)
            k = generated_numbers.size();
        k--;
        j--;
    }
}

void RandomNumberGenerator::f_displayParameters()
{
    std::cout << "\n\nc=" << adder << "\na=" << multiplier;
}

RandomNumberGenerator RandomNumberGenerator::generator;