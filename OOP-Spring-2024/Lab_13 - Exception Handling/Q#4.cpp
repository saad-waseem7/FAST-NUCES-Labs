#include <iostream>
using namespace std;

class DivisionByZeroException : public exception
{
public:
    const char *what() const noexcept override
    {
        return "Division by zero error";
    }
};

class Fraction
{
private:
    int numerator;
    int denominator;

public:
    Fraction(int num, int den) : numerator(num), denominator(den) {}

    void print() const
    {
        cout << numerator << "/" << denominator;
    }

    friend Fraction divide(const Fraction &f1, const Fraction &f2);
};

Fraction divide(const Fraction &f1, const Fraction &f2)
{
    if (f2.denominator == 0)
    {
        throw DivisionByZeroException();
    }

    int resultNumerator = f1.numerator * f2.denominator;
    int resultDenominator = f1.denominator * f2.numerator;

    return Fraction(resultNumerator, resultDenominator);
}

int main()
{
    try
    {
        Fraction fraction1(3, 4);
        Fraction fraction2(0, 2);

        cout << "Fraction 1: ";
        fraction1.print();
        cout << endl;

        cout << "Fraction 2: ";
        fraction2.print();
        cout << endl;

        Fraction result = divide(fraction1, fraction2);

        cout << "Result of division: ";
        result.print();
        cout << endl;
    }
    catch (const DivisionByZeroException &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
