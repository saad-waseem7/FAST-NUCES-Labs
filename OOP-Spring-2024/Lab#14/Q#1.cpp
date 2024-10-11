#include <iostream>
using namespace std;

// Part (a)
template <typename T>
T GetMax(T a, T b)
{
    return (a > b) ? a : b;
}

template <typename T>
T GetMin(T a, T b)
{
    return (a < b) ? a : b;
}
// Part (d)
template <typename T1, typename T2>
auto GetMax(T1 a, T2 b) -> decltype(a > b ? a : b)
{
    return (a > b) ? a : b;
}

template <typename T1, typename T2>
auto GetMin(T1 a, T2 b) -> decltype(a < b ? a : b)
{
    return (a < b) ? a : b;
}

// Part (b)
int main()
{
    /*
    int i = 5, j = 6, k;
    long l = 10, m = 5, n;
    k = GetMax<int>(i, j);
    n = GetMin<long>(l, m);
    cout << "PART C:" << endl;
    cout << k << endl;
    cout << n << endl;

    // Part (c)

    k = GetMax(i, j);
    n = GetMin(l, m);

    */
   
    // Part (d)
    char i = 'Z';
    int j = 6, k;
    long l = 10, m = 5, n;
    k = GetMax<int, long>(i, m);
    n = GetMin<int, char>(j, l);
    cout << "after revising the type conversion... " << endl;
    cout << "PART E:" << endl;
    cout << k << endl;
    cout << n << endl;

    // Part (e)
    k = GetMax(i, m);
    n = GetMin(j, l);

    return 0;
}
