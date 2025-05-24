#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
    int studentId;
    string name;
    char grade;
    float gpa;

public:
    Student(int id, const string &n, char g, float avg)
    {
        studentId = id;
        name = n;
        grade = g;
        gpa = avg;
    }

    int getStudentId()
    {
        return studentId;
    }

    void setStudentId(int id)
    {
        studentId = id;
    }

    string getName()
    {
        return name;
    }

    void setName(const string &n)
    {
        name = n;
    }

    char getGrade()
    {
        return grade;
    }

    void setGrade(char g)
    {
        grade = g;
    }

    float getGPA()
    {
        return gpa;
    }

    void setGPA(float avg)
    {
        gpa = avg;
    }
};

int main()
{
    int id;
    string name;
    char grade;
    float gpa;

    cout << "Enter Student ID: ";
    cin >> id;
    while (id <= 0)
    {
        cout << "Invalid Input. Please enter a valid ID: ";
        cin >> id;
    }

    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Grade: ";
    cin >> grade;
    while (grade < 'A' || grade > 'F')
    {
        if (grade < 'a' || grade > 'f')
        {
            cout << "Invalid Input. Please enter a valid Grade: ";
            cin >> grade;
        }
        else
        {
            break;
        }
    }

    cout << "Enter GPA: ";
    cin >> gpa;
    while (gpa < 0 || gpa > 4)
    {
        cout << "Invalid Input. Please enter a valid GPA: ";
        cin >> gpa;
    }

    Student s(id, name, grade, gpa);
    cout << "Student ID: " << s.getStudentId() << endl;
    cout << "Name: " << s.getName() << endl;
    cout << "Grade: " << s.getGrade() << endl;
    cout << "GPA: " << s.getGPA() << endl;

    cout << "Enter New Student ID: ";
    cin >> id;
    while (id <= 0)
    {
        cout << "Invalid Input. Please enter a valid ID: ";
        cin >> id;
    }

    cout << "Enter New Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter New Grade: ";
    cin >> grade;
    while (grade < 'A' || grade > 'F')
    {
        if (grade < 'a' || grade > 'f')
        {
            cout << "Invalid Input. Please enter a valid Grade: ";
            cin >> grade;
        }
        else
        {
            break;
        }
    }

    cout << "Enter New GPA: ";
    cin >> gpa;
    while (gpa < 0 || gpa > 4)
    {
        cout << "Invalid Input. Please enter a valid GPA: ";
        cin >> gpa;
    }

    s.setStudentId(id);
    s.setName(name);
    s.setGrade(grade);
    s.setGPA(gpa);

    cout << "Updated Student ID: " << s.getStudentId() << endl;
    cout << "Updated Name: " << s.getName() << endl;
    cout << "Updated Grade: " << s.getGrade() << endl;
    cout << "Updated GPA: " << s.getGPA() << endl;

    return 0;
}