#include <iostream>
using namespace std;

class ArrayIndexOutOfBoundsException : public exception
{
public:
    const char *what() const noexcept override
    {
        return "Array index out of bounds";
    }
};

int getElementAtIndex(int index, int arr[]);

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << " ";
    }
    try
    {
        int index;
        cout << "\nEnter an index to print Element: ";
        cin >> index;

        int value = getElementAtIndex(index, arr); 
        cout << "Value at index " << index << ": " << value << endl;
    }
    catch (const ArrayIndexOutOfBoundsException &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Unknown error occurred" << endl;
    }

    return 0;
}

int getElementAtIndex(int index, int arr[])
{
    if (index < 0 || index >= 5)
    {
        throw ArrayIndexOutOfBoundsException();
    }
    return arr[index];
}
