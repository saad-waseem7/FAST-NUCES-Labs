#include<iostream>
#include<string>
#include<cstring>
using namespace std;

class Student
{
private:
    string name;
    int roll;
    float cgpa;
public:
    Student();
    Student(string name, int roll, float cgpa);
    void set_name(string name);
    void set_roll(int roll);
    void set_cgpa(float cgpa);
    string get_name();
    int get_roll();
    float get_cgpa();
    void Print_Student();

    ~Student();
};

Student::Student()
{
    this->name = "";
    this->roll = 0;
    this->cgpa = 0.0;
}

Student::Student(string name, int roll, float cgpa)
{
    this->name = name;
    this->roll = roll;
    this->cgpa = cgpa;
}

void Student::set_name(string name)
{
    this->name = name;
}

void Student::set_roll(int roll)
{
    this->roll = roll;
}

void Student::set_cgpa(float cgpa)
{
    this->cgpa = cgpa;
}

string Student::get_name()
{
    return this->name;
}

int Student::get_roll()
{
    return this->roll;
}

float Student::get_cgpa()
{
    return this->cgpa;
}

void Student::Print_Student()
{
    cout << "Student Name: " << this->name << endl;
    cout << "Student Roll Number: " << this->roll << endl;
    cout << "Student CGPA: " << this->cgpa << endl;
}

Student::~Student()
{
    //Destructor Called
}

class Society
{
private:
    char name[50];
    Student* president;
    Student* members[5];
    int currentMembersCount;

public:

    Society();
    Society(const char* societyName);
    void PrintInfo();
    void AppointPresident(Student& student);
    void AddMember(Student* student);
    void SuspendMember(const char* memberName);
    ~Society();

};

Society::Society()
{
    strcpy_s(name, "No Name");
    president = nullptr;
    currentMembersCount = 0;
    for (int i = 0; i < 5; i++)
    {
        members[i] = nullptr;
    }
}

Society::Society(const char* societyName)
{
    strcpy_s(name, societyName);
    president = nullptr;
    currentMembersCount = 0;
    for (int i = 0; i < 5; i++)
    {
        members[i] = nullptr;
    }
}

void Society::PrintInfo()
{
    cout << "Society Name: " << name << endl;
    if (president != nullptr)
    {
        cout << "President: ";
        president->Print_Student();
    }
    else {
        cout << "President: Not Available" << endl;
    }
    for (int i = 0; i < 5; i++)
    {
        if (members[i] != nullptr)
        {
            cout << "Member " << i + 1 << ": ";
            members[i]->Print_Student();
        }
        else {
            cout << "Member " << i + 1 << ": Not Available" << endl;
        }
    }

}

void Society::AppointPresident(Student& student)
{
    if (president != nullptr)
    {
        cout << student.get_name() << " cannot be appointed as President. President position is NOT vacant." << endl;
    }
    else if (student.get_cgpa() <= 3.00)
    {
        cout << student.get_name() << " cannot be appointed as President. CGPA criteria not met." << endl;
    }
    else {
        president = &student;
        cout << student.get_name() << " has been appointed as President." << endl;
    }
}

void Society::AddMember(Student* student)
{
    if (president == student)
    {
        cout << "President cannot be added in Members list." << endl;
        return;
    }

    for (int i = 0; i < 5; i++)
    {
        if (members[i] == student)
        {
            cout << student->get_name() << " already exists in Members list." << endl;
            return;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (members[i] == nullptr)
        {
            members[i] = student;
            cout << student->get_name() << " has been added to members list successfully." << endl;
            currentMembersCount++;
            return;
        }
    }

    cout << "Robert Elen cannot be added to members list. Member position is NOT vacant." << endl;
}
void Society::SuspendMember(const char* memberName)
{
    bool found = false;
    for (int i = 0; i < 5; i++)
    {
        if (members[i] != nullptr && strcmp(members[i]->get_name().c_str(), memberName) == 0)
        {
            members[i] = nullptr;
            found = true;
            cout << memberName << " has been suspended from the Society." << endl;
            break;
        }
    }
    if (!found)
    {
        cout << memberName << " was not found in the Society members." << endl;
    }
}
Society::~Society()
{

}

int main() {

    Society sports("Sports");
    Student s1("Hashim Amla", 121111, 3.99);
    Student s2("Virat Kohli", 131121, 3.45);
    Student s3("Quinton de Kock", 131126, 2.98);
    Student s4("Joe Root", 141361, 2.99);
    Student s5("Martin Guptil", 141124, 3.09);
    Student s6("Rohit Sharma", 151314, 3.19);
    cout << endl;
    s1.Print_Student();
    s2.Print_Student();
    s3.Print_Student();
    s4.Print_Student();
    s5.Print_Student();
    s6.Print_Student();
    cout << endl;

    sports.AppointPresident(s3);
    cout << endl;
    sports.AppointPresident(s1);
    cout << endl;
    sports.AppointPresident(s2);
    cout << endl;

    cout << endl;
    sports.PrintInfo();
    cout << endl;

    cout << endl;
    Student s7("Robert Elen", 151334, 2.19);
    sports.AddMember(&s3);
    cout << endl;
    sports.AddMember(&s2);
    cout << endl;
    sports.AddMember(&s3);
    cout << endl;
    sports.AddMember(&s1);
    cout << endl;
    sports.AddMember(&s4);
    cout << endl;
    sports.AddMember(&s5);
    cout << endl;
    sports.AddMember(&s6);
    cout << endl;
    sports.AddMember(&s7);
    cout << endl;


    Society tech("Tech Society");
    Student a("Alia", 1, 3.50);
    Student b("Bobby", 2, 3.75);
    Student c("Cameron", 3, 2.75);
    Student d("David", 4, 3.25);
    Student e("Finch", 5, 3.90);
    tech.AppointPresident(a);
    cout << endl;
    tech.AddMember(&b);
    tech.AddMember(&c);
    tech.AddMember(&d);
    tech.AddMember(&e);
    cout << endl;
    tech.PrintInfo(); 
    cout << endl;
    tech.SuspendMember("David");
    cout << endl;
    tech.PrintInfo();
    cout << endl;

    return 0;
}