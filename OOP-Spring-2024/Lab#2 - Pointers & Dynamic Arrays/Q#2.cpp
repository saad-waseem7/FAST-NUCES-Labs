#include <iostream>
using namespace std;

void updateGrade(double *ptrGrade, double newGrade)
{
    *ptrGrade = newGrade;
}

void printGrade(const double &grade)
{
    cout << "Student's Updated grade: " << grade << endl;
}

int main()
{
    double studentGrade = 85.0;
    printGrade(studentGrade);
    cout << "Enter the new grade: ";
    double newGrade;
    cin >> newGrade;
    updateGrade(&studentGrade, newGrade);
    printGrade(studentGrade);

    return 0;
}