#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <functional>

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

class RandomNumberGenerator
{
private:
    std::vector<int> generated_numbers;
    std::vector<int> multipliers;
    std::vector<int> adders;
    std::vector<int> moduloPrimeNumbersDivisiers;
    std::vector<std::vector<int>> seeds;
    int multiplier, adder, modulo, first_x;

    //Uznałem, że bez sensu jest tworzenie wielu instancji, dlatego ukryłem konstruktor (zastosowałem Singleton)
    RandomNumberGenerator() : multiplier(0), adder(0), modulo(0), first_x(0) {};
    static RandomNumberGenerator generator;

    void f_clearStack()
    {
        while (!generated_numbers.empty())
        {
            generated_numbers.pop_back();
        }
    }

    void f_fillStackWithRandomNumbers(int quantity)
    {
        f_clearStack();
        generated_numbers.push_back(first_x % modulo);

        for (int i = 1; i < quantity; i++)
        {
            generated_numbers.push_back((multiplier * generated_numbers[generated_numbers.size() - 1] + adder) % modulo);
        }
    }

    void f_getModulo()
    {
        int max_value;
        std::cout << "Podaj najwieksza mozliwa wartosc: ";
        std::cin >> max_value;
        modulo = max_value + 1;
    }

    bool f_isPrime(int number)
    {
        if (number < 2)
            return false;
        for (int i = 2; i * i <= number; i++)
            if (number % i == 0)
                return false;
        return true;
    }

    void f_getModuloPrimeNumbersDivisiers()
    {
        for (int i = 2; i <= modulo; i++) {
            if (modulo % i == 0 && f_isPrime(i)) {
                moduloPrimeNumbersDivisiers.push_back(i);
            }
        }
    }

    int f_findGreatestCommonDivisier(int a, int b)
    {
        if (a == b) return a;
        return b == 0 ? a : f_findGreatestCommonDivisier(b, a % b);
    }

    void f_getAdders()
    {
        for (int i = 0; i < modulo; i++)
        {
            if (f_findGreatestCommonDivisier(modulo, i) == 1)
            {
                adders.push_back(i);
            }
        }
    }

    void f_getMultipliers()
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

    void f_getSeeds()
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

    void f_setSeed()
    {
        int seed = std::time(0) % seeds.size();
        first_x = seeds[seed][0];
        multiplier = seeds[seed][1];
        adder = seeds[seed][2];
    }
public:
    static RandomNumberGenerator& get()
    {
        return generator;
    }

    void f_generateRandomNumbers()
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

    void f_displayGeneratedNumbers() {
        for (int i = 0; i < generated_numbers.size(); i++)
        {
            std::cout << generated_numbers[i] << std::endl;
        }
        std::cout << std::endl;
    }

    void f_saveGeneratedNumbersInFile()
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

    void f_generateWithAdditiveCongruentMethod()
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

    void f_displayParameters()
    {
        std::cout << "\n\nc=" << adder << "\na=" << multiplier;
    }

};

RandomNumberGenerator RandomNumberGenerator::generator;


int main()
{
    RandomNumberGenerator test = RandomNumberGenerator::get();


    test.f_generateRandomNumbers();
    test.f_displayGeneratedNumbers();
    test.f_saveGeneratedNumbersInFile();
    test.f_displayParameters();
    test.f_displayGeneratedNumbers();
    test.f_saveGeneratedNumbersInFile();
    return 0;
}