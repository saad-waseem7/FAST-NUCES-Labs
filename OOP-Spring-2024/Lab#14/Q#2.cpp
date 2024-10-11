#include <iostream>
using namespace std;

template <class T>
class Pair
{
private:
    T values[2];

public:
    Pair(T first, T second)
    {
        values[0] = first;
        values[1] = second;
    }

    T GetMax() const
    {
        return values[0] > values[1] ? values[0] : values[1];
    }

    T GetMin() const;
};

template <class T>
T Pair<T>::GetMin() const
{
    return values[0] < values[1] ? values[0] : values[1];
}

template <class T>
class Container
{
public:
    T data;

    Container(T d) : data(d) {}

    T increase()
    {
        return ++data;
    }
};

template <>
class Container<char>
{
public:
    char data;

    Container(char d) : data(d) {}

    char uppercase()
    {
        if (data >= 'a' && data <= 'z')
        {
            data -= 32;
        }
        return data;
    }
};

int main()
{
    Pair<double> my_object(1.012, 1.01234);
    cout << "Maximum: " << my_object.GetMax() << endl;
    cout << "Minimum: " << my_object.GetMin() << endl;

    Container<int> myIntContainer(42);
    cout << "Increased: " << myIntContainer.increase() << endl;

    Container<char> myCharContainer('b');
    cout << "Uppercase: " << myCharContainer.uppercase() << endl;
    return 0;
}
