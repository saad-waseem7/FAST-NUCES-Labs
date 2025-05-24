#include <iostream>
using namespace std;
class Shape
{
protected:
    int positionX;
    int positionY;
    int size;

public:
    Shape(int posX, int posY, int sz);
    virtual void draw() = 0;
    virtual float calculate_area();
};

class Circle : public Shape
{
public:
    Circle(int posX, int posY, int radius);
    void draw() override;
    float calculate_area() override;

private:
    int radius;
};

class Rectangle : public Shape
{
public:
    Rectangle(int posX, int posY, int width, int height);
    void draw() override;
    float calculate_area() override;

private:
    int width;
    int height;
};

class Triangle : public Shape
{
public:
    Triangle(int posX, int posY, int base, int height);
    void draw() override;
    float calculate_area() override;

private:
    int base;
    int height;
};

Shape::Shape(int posX, int posY, int sz) : positionX(posX), positionY(posY), size(sz) {}

float Shape::calculate_area()
{
    return 0;
}

Circle::Circle(int posX, int posY, int r) : Shape(posX, posY, r), radius(r) {}

void Circle::draw()
{
    cout << "Drawing a circle at position (" << positionX << ", " << positionY << ") with radius " << radius << endl;
}

float Circle::calculate_area()
{
    return 3.14159 * radius * radius;
}

Rectangle::Rectangle(int posX, int posY, int w, int h) : Shape(posX, posY, w * h), width(w), height(h) {}

void Rectangle::draw()
{
    cout << "Drawing a rectangle at position (" << positionX << ", " << positionY << ") with width " << width << " and height " << height << endl;
}

float Rectangle::calculate_area()
{
    return width * height;
}

Triangle::Triangle(int posX, int posY, int b, int h) : Shape(posX, posY, (b * h) / 2), base(b), height(h) {}

void Triangle::draw()
{
    cout << "Drawing a triangle at position (" << positionX << ", " << positionY << ") with base " << base << " and height " << height << endl;
}

float Triangle::calculate_area()
{
    return (base * height) / 2;
}

int main()
{
    Circle circle(5, 5, 3);
    circle.draw();
    cout << "Area of the circle: " << circle.calculate_area() << endl;
    cout << endl;
    Rectangle rectangle(10, 10, 4, 6);
    rectangle.draw();
    cout << "Area of the rectangle: " << rectangle.calculate_area() << endl;
    cout << endl;
    Triangle triangle(0, 0, 4, 5);
    triangle.draw();
    cout << "Area of the triangle: " << triangle.calculate_area() << endl;

    return 0;
}
