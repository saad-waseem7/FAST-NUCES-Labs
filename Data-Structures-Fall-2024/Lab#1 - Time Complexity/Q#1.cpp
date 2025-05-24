// The overall time complexity of the following C++ program is O(1), which means it is constant time.

#include <iostream>
#include <string>
using namespace std;

class Shape
{
private:
    string color;

public:
    Shape(string color);
    ~Shape();

    void set_color(const string color);
    string get_color() const;
    virtual void print_data() const;
};

Shape::Shape(string color) : color(color)
{
}

Shape::~Shape()
{
}

void Shape::set_color(const string color)
{
    this->color = color;
}

string Shape::get_color() const
{
    return this->color;
}

void Shape::print_data() const
{
    cout << "Color: " << this->color << endl;
}

class Circle : public Shape
{
private:
    double radius;

public:
    Circle(const string color, double radius);
    ~Circle();

    void print_data() const override;
};

Circle::Circle(const string color, double radius) : Shape(color)
{
    this->radius = radius;
}

Circle::~Circle()
{
}

void Circle::print_data() const
{
    Shape::print_data();
    cout << "Radius: " << this->radius << endl;
}

int main()
{
    Circle circle("Green", 7);
    circle.print_data();
    return 0;
}
