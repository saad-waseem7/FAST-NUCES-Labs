#include <iostream>
#include <cmath>
using namespace std;
class Shape
{
public:
    virtual double calculateArea() const = 0;
};

class Circle : public Shape
{
private:
    double radius;

public:
    Circle(double r) : radius(r) {}
    double calculateArea() const override
    {
        return 3.14159 * radius * radius;
    }
};

class Rectangle : public Shape
{
private:
    double length;
    double width;

public:
    Rectangle(double l, double w) : length(l), width(w) {}
    double calculateArea() const override
    {
        return length * width;
    }
};

class Triangle : public Shape
{
private:
    double base;
    double height;

public:
    Triangle(double b, double h) : base(b), height(h) {}
    double calculateArea() const override
    {
        return 0.5 * base * height;
    }
};

int main()
{
    const int numShapes = 3;
    Shape *shapes[numShapes];

    *(shapes + 0) = new Circle(7);
    *(shapes + 1) = new Rectangle(7, 9);
    *(shapes + 2) = new Triangle(7, 3);

    for (int i = 0; i < numShapes; ++i)
    {
        cout << "Area of shape " << i << " is: " << shapes[i]->calculateArea() << endl;
        delete *(shapes + i);
    }

    return 0;
}