#include <iostream>
#include <string>

using namespace std;

string decodeRecursive(const string &str, int &count)
{
    string result = "";
    int i;
    for (i = 0; count < str.size() && str[count] != ']'; i++)
    {
        if (isdigit(str[count]))
        {
            int num = 0;
            while (isdigit(str[count]))
            {
                num = num * 10 + (str[count] - '0');
                count++;
            }
            count++;
            string decoded = decodeRecursive(str, count);
            count++;
            while (num--)
            {
                result += decoded;
            }
        }
        else
        {
            result += str[count++];
        }
    }

    return result;
}

string decode(const string &str)
{
    int count = 0;
    return decodeRecursive(str, count);
}

int main()
{
    string str1 = "3[a]2[bc]";
    string str2 = "3[a2[c]]";

    cout << decode(str1) << endl;
    cout << decode(str2) << endl;

    return 0;
}