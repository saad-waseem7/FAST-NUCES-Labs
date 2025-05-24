#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isBalanced(string exp)
{
    stack<char> st;

    for (char c : exp)
    {
        if (c == '(' || c == '{' || c == '[')
        {
            st.push(c);
        }
        else if (c == ')' || c == '}' || c == ']')
        {
            if (st.empty())
                return false;
            char top = st.top();
            st.pop();
            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '['))
            {
                return false;
            }
        }
    }

    return st.empty();
}

int main()
{
    string exp = "{[{}{}]}[()]";
    if (isBalanced(exp))
    {
        cout << "The expression is balanced." << endl;
    }
    else
    {
        cout << "The expression is not balanced." << endl;
    }

    return 0;
}
