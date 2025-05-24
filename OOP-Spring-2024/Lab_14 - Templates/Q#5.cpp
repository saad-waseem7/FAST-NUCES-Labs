
#include <iostream>
using namespace std;

template <typename T>
class Pair
{
private:
    T first;
    T second;

public:
    Pair() : first(T()), second(T()) {} // default constructor
    Pair(T f, T s) : first(f), second(s) {}

    T getFirst() const { return first; }
    T getSecond() const { return second; }

    template <typename U>
    friend ostream &operator<<(ostream &out, const Pair<U> &p)
    {
        out << "(" << p.getFirst() << ", " << p.getSecond() << ")";
        return out;
    }
};

template <typename T, int N>
class Sequence
{
private:
    T data[N];

public:
    void set_member(int index, const T &value)
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

    T get_member(int index) const
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
    Pair<double> y(2.23, 3.45);
    Sequence<Pair<double>, 5> myPairs;
    myPairs.set_member(0, y);
    cout << myPairs.get_member(0) << '\n';
    return 0;
}
