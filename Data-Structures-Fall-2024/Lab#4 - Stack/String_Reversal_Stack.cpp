#include <iostream>
#include <stack>
#include <string>
using namespace std;

string reverse(string const &str)
{
    stack<char> st;
    for (char c : str)
    {
        st.push(c);
    }

    string reversed = "";
    while (!st.empty())
    {
        reversed += st.top();
        st.pop();
    }

    return reversed;
}

int main()
{
    string str = "Hello World!";
    cout << "Reversed: " << reverse(str) << endl;

    return 0;
}
