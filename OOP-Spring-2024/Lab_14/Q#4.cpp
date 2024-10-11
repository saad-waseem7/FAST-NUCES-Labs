
#include <iostream>
using namespace std;

template <typename T, int N>
class Sequence
{
private:
    T data[N];

public:
    void set_member(int index, T value)
    {
        if (index >= 0 && index < N)
        {
            data[index] = value;
        }
        else
        {
            cerr << "Index out of bounds" << endl;
        }
    }

    T get_member(int index)
    {
        if (index >= 0 && index < N)
        {
            return data[index];
        }
        else
        {
            cerr << "Index out of bounds" << endl;
            return T(); // return default value for type T
        }
    }
};

int main()
{
    Sequence<int, 5> my_ints;
    Sequence<double, 5> my_floats;
    my_ints.set_member(0, 100);
    my_floats.set_member(3, 3.1416);
    cout << my_ints.get_member(0) << '\n';
    cout << my_floats.get_member(3) << '\n';
    return 0;
}
