#include <iostream>
using namespace std;

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
            data -= ('a' - 'A');
        }
        return data;
    }
};

template <class T, int N>
class Sequence
{
public:
    T mem_block[N];

    void setMember(int x, T value)
    {
        if (x >= 0 && x < N)
        {
            mem_block[x] = value;
        }
    }

    T getMember(int x)
    {
        if (x >= 0 && x < N)
        {
            return mem_block[x];
        }
        return T();
    }
};

int main()
{
    Container<int> my_int(7);
    Container<char> my_char('j');
    cout << "Increased integer: " << my_int.increase() << endl;
    cout << "Uppercase character: " << my_char.uppercase() << endl;
    return 0;
}
