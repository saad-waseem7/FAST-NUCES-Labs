#include <iostream>
#include <cmath>
using namespace std;
double add(double a, double b)
{
    if (isnan(a) || isnan(b))
    {
        throw invalid_argument("Invalid argument: non-numeric value passed");
    }
    return a + b;
}

int main()
{
    try
    {
        double result = add(5.0, 3.0);
        cout << "Result: " << result << endl;
        result = add(5.0, NAN);
        cout << "Result: " << result << endl;
    }
    catch (...)
    {
        cout << "Exception caught: Invalid argument: non-numeric value passed" << endl;
    }
    return 0;
}
