#include <iostream>
using namespace std;
class Complex
{
private:
	int real;
	int img;

public:
	Complex(int r = 0, int i = 0) {
		real = r;
		img = i;
	}

	friend ostream& operator<<(ostream&, Complex&);
	friend istream& operator>>(istream&, Complex&);

	Complex operator+(Complex&);
	Complex operator-(Complex&);
	Complex operator*(Complex&);
};


Complex Complex::operator+(Complex& temp)
{
	int new_real= real + temp.real;
	int new_img = img + temp.img;
	return Complex(new_real, new_img);
}

Complex Complex::operator-(Complex& temp)
{
	int new_real = real - temp.real;
	int new_img = img - temp.img;
	return Complex(new_real, new_img);
}

Complex Complex::operator*(Complex& temp)
{
	int new_real = real * temp.real;
	int new_img = img * temp.img;
	return Complex(new_real, new_img);
}

ostream& operator<<(ostream& os, Complex& complex)
{
	os << "(" << complex.real << ", " << complex.img << ")";
	return os;
}

istream& operator>>(istream& is, Complex& complex)
{
	cout << "Enter real part: ";
	is >> complex.real;
	cout << "Enter imaginary part: ";
	is >> complex.img;
	return is;
}

int main()
{
	Complex c1, c2, c3;

	cin >> c1 >> c2;

	Complex sum = c1 + c2;
	Complex diff = c1 - c2;
	Complex prod = c1 * c2;

	cout << "Sum: " << sum << "\n";
	cout << "Difference: " << diff << "\n";
	cout << "Product: " << prod << "\n";

	return 0;
}