#include <iostream>
using namespace std;

class Time
{
private:
public:
    int hours, minutes, seconds;
    Time(int h = 0, int m = 0, int s = 0)
    {
        hours = h;
        minutes = m;
        seconds = s;
    }

    Time operator+(const Time &temp);
    Time operator-(const Time &temp);
    Time &operator++();
    Time &operator--();
    bool operator==(const Time &temp);
    bool operator!=(const Time &temp);
};

Time Time::operator+(const Time &temp)
{
    int h = hours + temp.hours;
    int m = minutes + temp.minutes;
    int s = seconds + temp.seconds;

    if (s >= 60)
    {
        m += s / 60;
        s %= 60;
    }
    if (m >= 60)
    {
        h += m / 60;
        m %= 60;
    }
    if (h >= 24)
    {
        h %= 24;
    }

    return Time(h, m, s);
}

Time Time::operator-(const Time &temp)
{
    int h = hours - temp.hours;
    int m = minutes - temp.minutes;
    int s = seconds - temp.seconds;

    if (s < 0)
    {
        m--;
        s += 60;
    }
    if (m < 0)
    {
        h--;
        m += 60;
    }
    if (h < 0)
    {
        h += 24;
    }

    return Time(h, m, s);
}

Time &Time::operator++()
{
    seconds++;
    if (seconds >= 60)
    {
        minutes++;
        seconds -= 60;
        if (minutes >= 60)
        {
            hours++;
            minutes -= 60;
            if (hours >= 24)
            {
                hours -= 24;
            }
        }
    }
    return *this;
}

Time &Time::operator--()
{
    seconds--;
    if (seconds < 0)
    {
        minutes--;
        seconds += 60;
        if (minutes < 0)
        {
            hours--;
            minutes += 60;
            if (hours < 0)
            {
                hours += 24;
            }
        }
    }
    return *this;
}

bool Time::operator==(const Time &temp)
{
    if (hours == temp.hours && minutes == temp.minutes && seconds == temp.seconds)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Time::operator!=(const Time &temp)
{
    if (!(*this == temp))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    /*
    int a, b, c, d, e, f;
    cout << "Enter Data for First Object :\n";
    cout << "Enter Hours: \n";
    cin >> a;
    cout << "Enter Minutes: \n";
    cin >> b;
    cout << "Enter Seconds: \n";
    cin >> c;
    cout << "Enter Data for Second Object :\n";
    cout << "Enter Hours: \n";
    cin >> d;
    cout << "Enter Minutes: \n";
    cin >> e;
    cout << "Enter Seconds: \n";
    cin >> f;

    Time t1(a, b, c);
    Time t2(d, e, f);
    */

    Time t1(11, 59, 59);
    Time t2(12, 0, 0);

    Time t3 = t1 + t2;
    cout << "t1 + t2 = " << t3.hours << ":" << t3.minutes << ":" << t3.seconds << endl;

    Time t4 = t2 - t1;
    cout << "t2 - t1 = " << t4.hours << ":" << t4.minutes << ":" << t4.seconds << endl;

    ++t1;
    cout << "++t1 = " << t1.hours << ":" << t1.minutes << ":" << t1.seconds << endl;

    --t2;
    cout << "--t2 = " << t2.hours << ":" << t2.minutes << ":" << t2.seconds << endl;

    if (t1 == t2)
    {
        cout << "t1 is equal to t2" << endl;
    }
    else
    {
        cout << "t1 is not equal to t2" << endl;
    }

    if (t1 != t3)
    {
        cout << "t1 is not equal to t3" << endl;
    }
    else
    {
        cout << "t1 is equal to t3" << endl;
    }

    return 0;
}