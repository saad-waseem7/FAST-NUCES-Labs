#include <iostream>
using namespace std;

class Distance
{
private:
public:
    int meters;
    Distance(int m = 0)
    {
        meters = m;
    }

    bool operator<(Distance &temp);
    bool operator>(Distance &temp);
    bool operator<=(Distance &temp);
    bool operator>=(Distance &temp);
    Distance operator+=(int m);
    Distance operator-=(int m);
};

bool Distance::operator<(Distance &temp)
{
    if (meters < temp.meters)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Distance::operator>(Distance &temp)
{
    if (meters > temp.meters)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Distance::operator<=(Distance &temp)
{
    if (meters <= temp.meters)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Distance::operator>=(Distance &temp)
{
    if (meters >= temp.meters)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Distance Distance::operator+=(int m)
{
    meters += m;
    return *this;
}

Distance Distance::operator-=(int m)
{
    meters -= m;
    return *this;
}

int main()
{
    int a, b;
    cout << "Enter First Distance: \n";
    cin >> a;
    cout << "Enter Second Distance: \n";
    cin >> b;
    Distance d1(a);
    Distance d2(b);

    if (d1 < d2)
    {
        cout << "D1 is less than D2" << endl;
    }

    if (d1 > d2)
    {
        cout << "D1 is greater than D2" << endl;
    }

    if (d1 <= d2)
    {
        cout << "D1 is less than or equal to D2" << endl;
    }

    if (d1 >= d2)
    {
        cout << "D1 is greater than or equal to D2" << endl;
    }

    int c, d;
    cout << "Enter Value to Add Into Current Distance: \n";
    cin >> c;
    d1 += c;
    cout << "D1 is now " << d1.meters << " meters" << endl;
    cout << "Enter Value to Subtract From Current Distance: \n";
    cin >> d;
    d1 -= d;
    cout << "D1 is now " << d1.meters << " meters" << endl;

    return 0;
}