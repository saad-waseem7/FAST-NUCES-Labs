#include <iostream>
#include <string>
using namespace std;

class Roman
{
private:
    int value;

public:
    Roman(int value);
    ~Roman();
    string toRoman() const;

    Roman &operator++();
    Roman operator++(int);

    Roman &operator--();
    Roman operator--(int);

    bool operator==(const Roman &num) const;
    bool operator!=(const Roman &num) const;
    bool operator<(const Roman &num) const;
    bool operator>(const Roman &num) const;

    friend Roman operator+(const Roman &num1, const Roman &num2);
    friend Roman operator-(const Roman &num1, const Roman &num2);
    friend Roman operator*(const Roman &num1, const Roman &num2);
    friend Roman operator/(const Roman &num1, const Roman &num2);
};

Roman::Roman(int value)
{
    this->value = value;
}

Roman::~Roman()
{
    // cout << "Destructor called" << endl;
}

string Roman ::toRoman() const
{
    string roman;
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const string numerals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    if (value == 0)
    {
        return "0";
    }
    int num;
    if (value < 0)
    {
        num = -value;

        for (int i = 0; i < 13; ++i)
        {
            while (num >= values[i])
            {
                num -= values[i];
                roman += numerals[i];
            }
        }
        return "-" + roman;
    }
    else
    {
        num = value;

        for (int i = 0; i < 13; ++i)
        {
            while (num >= values[i])
            {
                num -= values[i];
                roman += numerals[i];
            }
        }
        return roman;
    }
}

Roman &Roman::operator++()
{
    ++value;
    return *this;
}

Roman Roman::operator++(int)
{
    Roman temp = *this;
    ++(*this);
    return temp;
}

Roman &Roman::operator--()
{
    --value;
    return *this;
}

Roman Roman::operator--(int)
{
    Roman temp = *this;
    --(*this);
    return temp;
}

bool Roman::operator==(const Roman &num) const
{
    if (value == num.value)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Roman::operator!=(const Roman &num) const
{
    if (!(*this == num))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Roman::operator<(const Roman &num) const
{
    if (value < num.value)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Roman::operator>(const Roman &num) const
{
    if (value > num.value)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Roman operator+(const Roman &num1, const Roman &num2)
{
    int result = 0;
    result = num1.value + num2.value;
    return Roman(result);
}

Roman operator-(const Roman &num1, const Roman &num2)
{
    int result = 0;
    result = num1.value - num2.value;
    return Roman(result);
}

Roman operator*(const Roman &num1, const Roman &num2)
{
    int result = 0;
    result = num1.value * num2.value;
    return Roman(result);
}

Roman operator/(const Roman &num1, const Roman &num2)
{
    int result = 0;
    result = num1.value / num2.value;
    return Roman(result);
}

int toInt(const string &roman)
{
    int result = 0;

    for (int i = 0; i < roman.size(); ++i)
    {
        if (roman[i] == 'M')
        {
            result += 1000;
        }
        else if (roman[i] == 'D')
        {
            result += 500;
        }
        else if (roman[i] == 'C')
        {
            if (i + 1 < roman.size() && (roman[i + 1] == 'M' || roman[i + 1] == 'D'))
            {
                result -= 100;
            }
            else
            {
                result += 100;
            }
        }
        else if (roman[i] == 'L')
        {
            result += 50;
        }
        else if (roman[i] == 'X')
        {
            if (i + 1 < roman.size() && (roman[i + 1] == 'C' || roman[i + 1] == 'L'))
            {
                result -= 10;
            }
            else
            {
                result += 10;
            }
        }
        else if (roman[i] == 'V')
        {
            result += 5;
        }
        else if (roman[i] == 'I')
        {
            if (i + 1 < roman.size() && (roman[i + 1] == 'X' || roman[i + 1] == 'V'))
            {
                result -= 1;
            }
            else
            {
                result += 1;
            }
        }
    }

    return result;
}
bool isValidRoman(const string &str)
{
    string validChars = "IVXLCDM";
    for (int i = 0; i < str.length(); ++i)
    {
        char c = str[i];
        if (validChars.find(c) == -1)

        {
            return false;
        }
    }
    return true;
}

int main()
{
    int num1, num2;
    string n1, n2;
    char op;

    cout << "Enter a Roman number: ";
    cin >> n1;
    while (!isValidRoman(n1))
    {
        cout << "Invalid input! Please enter a valid Roman numeral: ";
        cin >> n1;
    }
    cout << "Enter another Roman number: ";
    cin >> n2;
    while (!isValidRoman(n2))
    {
        cout << "Invalid input! Please enter a valid Roman numeral: ";
        cin >> n2;
    }

    num1 = toInt(n1);
    num2 = toInt(n2);

    while (true)
    {
        cout << "Enter the operation (+, -, *, /,<,>): ";
        cin >> op;

        if (op == '+' || op == '-' || op == '*' || op == '/' || op == '<' || op == '>')
        {
            break;
        }
        else
        {
            cout << "Invalid operation\n";
        }
    }

    Roman romanNum1(num1);
    Roman romanNum2(num2);
    Roman result(0);

    if (op == '+')
    {
        result = romanNum1 + romanNum2;
    }
    else if (op == '-')
    {
        result = romanNum1 - romanNum2;
    }
    else if (op == '*')
    {
        result = romanNum1 * romanNum2;
    }
    else if (op == '/')
    {
        result = romanNum1 / romanNum2;
    }
    else if (op == '<')
    {
        if (romanNum1 < romanNum2)
        {
            cout << "True\n";
        }
        else
        {
            cout << "False\n";
        }
    }
    else if (op == '>')
    {
        if (romanNum1 > romanNum2)
        {
            cout << "True\n";
        }
        else
        {
            cout << "False\n";
        }
    }
    else
    {
        cout << "Invalid operation\n";
        return 1;
    }

    cout << "Result in Roman numerals: " << result.toRoman() << endl;

    cout << "Do You Want to see the Pre-Increment and Post-Increment of Result?\n";
    char choice;

    bool validChoice = false;
    while (!validChoice)
    {
        cin >> choice;
        if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N')
        {
            validChoice = true;
        }
        else
        {
            cout << "Invalid choice. Please enter 'y' or 'n': ";
        }
    }

    if (choice == 'y' || choice == 'Y')
    {
        ++result;
        cout << "Pre-Increment: ";
        Roman pre_incremented = result;
        cout << pre_incremented.toRoman() << endl;
        result++;
        cout << "Post-Increment: ";
        Roman post_incremented = result;
        cout << post_incremented.toRoman() << endl;
        --result;
        cout << "Pre-Decrement: ";
        Roman pre_decremented = result;
        cout << pre_decremented.toRoman() << endl;
        result--;
        cout << "Post-Decrement: ";
        Roman post_decremented = result;
        cout << post_decremented.toRoman() << endl;
    }
    else if (choice == 'n' || choice == 'N')
    {
        cout << "Exiting..." << endl;
    }

    return 0;
}
