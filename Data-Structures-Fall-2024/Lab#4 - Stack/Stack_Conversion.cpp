// Underdevelopment...

#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Function to reverse a string manually
void manualReverse(string &str)
{
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
    {
        swap(str[i], str[n - i - 1]); // Swap characters from start and end
    }
}

// Function precedence
int precedence(char c)
{
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return 0;
}

// Infix to Postfix Conversion
string infixToPostfix(string infix)
{
    stack<char> st;
    string postfix = "";

    for (char c : infix)
    {
        if (isalnum(c))
        {
            postfix += c; // Add operands directly to result
        }
        else if (c == '(')
        {
            st.push(c); // Push '(' to stack
        }
        else if (c == ')')
        {
            while (!st.empty() && st.top() != '(')
            {
                postfix += st.top(); // Pop until '(' is found
                st.pop();
            }
            st.pop(); // Remove '(' from stack
        }
        else
        {
            while (!st.empty() && precedence(st.top()) >= precedence(c))
            {
                postfix += st.top(); // Pop higher or equal precedence operators
                st.pop();
            }
            st.push(c); // Push current operator
        }
    }

    // Pop remaining operators in the stack
    while (!st.empty())
    {
        postfix += st.top();
        st.pop();
    }

    return postfix;
}

// Infix to Prefix Conversion
string infixToPrefix(string infix)
{
    // Manually reverse the infix expression
    manualReverse(infix);

    // Reverse the brackets
    for (char &c : infix)
    {
        if (c == '(')
            c = ')';
        else if (c == ')')
            c = '(';
    }

    // Convert the reversed infix to postfix
    string prefix = infixToPostfix(infix);

    // Manually reverse the postfix to get prefix
    manualReverse(prefix);

    return prefix;
}

int main()
{
    string infix = "(A + B) * (C - D)";

    cout << "Postfix: " << infixToPostfix(infix) << endl;
    cout << "Prefix: " << infixToPrefix(infix) << endl;

    return 0;
}
