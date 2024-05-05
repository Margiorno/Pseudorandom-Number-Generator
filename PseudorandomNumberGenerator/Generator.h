#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <fstream>
#include <time.h>
#include "OtherFunctions.h"

class RandomNumberGenerator
{
private:
    std::vector<int> generated_numbers;
    std::vector<int> multipliers;
    std::vector<int> adders;
    std::vector<int> moduloPrimeNumbersDivisiers;
    std::vector<std::vector<int>> seeds;
    int multiplier, adder, modulo, first_x;

    //Uzna³em, ¿e bez sensu jest tworzenie wielu instancji, dlatego ukry³em konstruktor (zastosowa³em Singleton)
    RandomNumberGenerator() : multiplier(0), adder(0), modulo(0), first_x(0) {};
    static RandomNumberGenerator generator;

    void f_clearStack();

    void f_fillStackWithRandomNumbers(int quantity);

    void f_getModulo();

    bool f_isPrime(int number);

    void f_getModuloPrimeNumbersDivisiers();

    int f_findGreatestCommonDivisier(int a, int b);

    void f_getAdders();

    void f_getMultipliers();

    void f_getSeeds();

    void f_setSeed();
public:
    static RandomNumberGenerator& get();

    void f_generateRandomNumbers();

    void f_displayGeneratedNumbers();

    void f_saveGeneratedNumbersInFile();

    void f_generateWithAdditiveCongruentMethod();

    void f_displayParameters();
};

#endif