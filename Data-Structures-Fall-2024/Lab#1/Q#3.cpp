// For operations like setting and getting individual elements, the time complexity remains constant at O(1).
// The time complexity of using the display() method makes it O(n).

#include <iostream>
using namespace std;

class DynamicArray
{
private:
    int *array;
    int size;

public:
    DynamicArray(int size);
    ~DynamicArray();

    void set_element(int index, int value);
    int get_element(int index) const;
    void display() const;
};

DynamicArray::DynamicArray(int size)
{
    this->size = size;
    array = new int[size];
}

DynamicArray::~DynamicArray()
{
    delete[] array;
}

void DynamicArray::set_element(int index, int value)
{
    if (index >= 0 && index < size)
    {
        array[index] = value;
    }
    else
    {
        cout << "Index out of bounds." << endl;
    }
}

int DynamicArray::get_element(int index) const
{
    if (index >= 0 && index < size)
    {
        return array[index];
    }
    else
    {
        cout << "Index out of bounds." << endl;
        return -1;
    }
}

void DynamicArray::display() const
{
    for (int i = 0; i < size; i++)
    {
        cout << "Element " << i << ": " << array[i] << endl;
    }
}

int main()
{
    DynamicArray dynamicArray(5);
    dynamicArray.set_element(0, 20);
    dynamicArray.set_element(1, 30);
    dynamicArray.set_element(2, 40);
    dynamicArray.set_element(3, 50);
    dynamicArray.set_element(4, 60);

    dynamicArray.display();

    dynamicArray.set_element(5, 70);
    dynamicArray.get_element(6);

    return 0;
}
