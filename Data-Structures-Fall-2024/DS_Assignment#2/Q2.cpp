#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
using namespace std;

class Information_Incomplete_Exception : public runtime_error
{
public:
    Information_Incomplete_Exception() : runtime_error("Incomplete patient information!") {}
};

class Priority_Validity_Exception : public runtime_error
{
public:
    Priority_Validity_Exception() : runtime_error("Invalid priority!") {}
};

class Serving_Delayed_Exception : public runtime_error
{
public:
    Serving_Delayed_Exception() : runtime_error("Patient serving getting delayed!") {}
};

class Patient
{
    string name;
    int age;
    string condition;
    bool reference;
    int priority;

public:
    Patient() : name(""), age(0), condition(""), priority(5), reference(false) {}

    Patient(string name, int age, string condition, bool ref) : name(name), age(age), reference(ref)
    {
        if (condition == "Normal" || condition == "Critical" || condition == "Intense" || condition == "normal" || condition == "critical" || condition == "intense")
        {
            this->condition = condition;
        }
        else
        {
            throw invalid_argument("Invalid Arguments for Condition");
        }
        derivePriority();
    }

    void updateInfo(string name, int age, string condition, bool ref)
    {
        if (name.empty() || condition.empty() || age == 0)
        {
            throw Information_Incomplete_Exception();
        }

        this->name = name;
        this->age = age;
        this->reference = ref;

        if (condition == "Normal" || condition == "Critical" || condition == "Intense")
        {
            this->condition = condition;
        }
        else
        {
            throw invalid_argument("Invalid Arguments for Condition");
        }

        derivePriority();
    }

    int derivePriority()
    {
        if (reference)
        {
            priority = 1;
        }
        else if (age >= 60)
        {
            priority = 2;
        }
        else if (condition == "Intense")
        {
            priority = 3;
        }
        else if (condition == "Critical")
        {
            priority = 4;
        }
        else if (condition == "Normal")
        {
            priority = 5;
        }
        else
        {
            throw Priority_Validity_Exception();
        }
        return priority;
    }

    int getPriority() const { return priority; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getCondition() const { return condition; }
    bool isSenior() const { return age >= 60; }

    void display() const
    {
        cout << "Name: " << name << ", Age: " << age
             << ", Condition: " << condition << ", Priority: " << priority << endl;
    }
};

void prioritizePatients(Patient p, queue<Patient> &high_priority, queue<Patient> &medium_priority, queue<Patient> &low_priority)
{
    int priority = p.getPriority();

    if (priority == 1 || priority == 2 || priority == 3)
    {
        high_priority.push(p);
    }
    else if (priority == 4)
    {
        medium_priority.push(p);
    }
    else
    {
        low_priority.push(p);
    }
}

queue<Patient> combineQueues(queue<Patient> &high_priority, queue<Patient> &medium_priority, queue<Patient> &low_priority)
{
    queue<Patient> finalQueue;

    while (!high_priority.empty())
    {
        finalQueue.push(high_priority.front());
        high_priority.pop();
    }
    while (!medium_priority.empty())
    {
        finalQueue.push(medium_priority.front());
        medium_priority.pop();
    }
    while (!low_priority.empty())
    {
        finalQueue.push(low_priority.front());
        low_priority.pop();
    }

    return finalQueue;
}

void displayCurrentPatients(queue<Patient> high_priority, queue<Patient> medium_priority, queue<Patient> low_priority)
{
    cout << "\nHigh-priority patients:" << endl;
    if (high_priority.empty())
    {
        cout << "None" << endl;
    }
    else
    {
        while (!high_priority.empty())
        {
            high_priority.front().display();
            high_priority.pop();
        }
    }

    cout << "\nMedium-priority patients:" << endl;
    if (medium_priority.empty())
    {
        cout << "None" << endl;
    }
    else
    {
        while (!medium_priority.empty())
        {
            medium_priority.front().display();
            medium_priority.pop();
        }
    }

    cout << "\nLow-priority patients:" << endl;
    if (low_priority.empty())
    {
        cout << "None" << endl;
    }
    else
    {
        while (!low_priority.empty())
        {
            low_priority.front().display();
            low_priority.pop();
        }
    }
}

void servePatients(queue<Patient> &finalQueue)
{
    int nonSeniorCount = 0, patientCount = 0;
    queue<Patient> tempQueue;

    while (!finalQueue.empty())
    {
        Patient current = finalQueue.front();
        finalQueue.pop();

        if (current.isSenior())
        {
            if (nonSeniorCount >= 3)
            {
                cout << "Serving senior patient due to wait limit: " << endl;
                current.display();
                nonSeniorCount = 0;
            }
            else
            {
                tempQueue.push(current);
            }
        }
        else
        {
            cout << "Serving non-senior patient: " << endl;
            current.display();
            nonSeniorCount++;
        }

        if (nonSeniorCount >= 3 && !tempQueue.empty())
        {
            Patient seniorPatient = tempQueue.front();
            tempQueue.pop();
            cout << "Serving senior patient due to wait limit: " << endl;
            seniorPatient.display();
            nonSeniorCount = 0;
        }
    }

    while (!tempQueue.empty())
    {
        Patient seniorPatient = tempQueue.front();
        tempQueue.pop();
        cout << "Serving remaining senior patient: " << endl;
        seniorPatient.display();
    }

    cout << "All patients have been served." << endl;
}

int main()
{
    queue<Patient> high_priority, medium_priority, low_priority;

    try
    {
        string name, condition;
        int age;
        bool reference;
        char choice;
        do
        {
            cout << "\nChoose from following options: \n1. Add a new patient \n2. Check the current status of patients \n3. Serve the current patients \n\n>>>Enter Option: ";
            cin >> choice;

            switch (choice)
            {
            case '1':
            {
                cout << "Enter name of patient: ";
                cin >> name;

                cout << "Enter age of patient: ";
                cin >> age;

                cout << "Enter patient condition (Normal, Critical, Intense): ";
                cin >> condition;

                cout << "Does the patient have a strong reference? (1 for yes, 0 for no): ";
                cin >> reference;

                try
                {
                    Patient new_patient(name, age, condition, reference);
                    prioritizePatients(new_patient, high_priority, medium_priority, low_priority);
                    cout << "Patient added successfully!" << endl;
                }
                catch (const exception &e)
                {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
            case '2':
                displayCurrentPatients(high_priority, medium_priority, low_priority);
                break;

            case '3':
            {
                queue<Patient> finalQueue = combineQueues(high_priority, medium_priority, low_priority);
                cout << "Serving patients based on priority:" << endl;
                servePatients(finalQueue);
                break;
            }

            default:
                cout << "Invalid choice! Please enter 1, 2, or 3." << endl;
                break;
            }

            cout << "Do you want to continue? (y/n): ";
            cin >> choice;

        } while (choice == 'y' || choice == 'Y');
    }
    catch (const Information_Incomplete_Exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch (const Priority_Validity_Exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch (const Serving_Delayed_Exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch (const invalid_argument &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
