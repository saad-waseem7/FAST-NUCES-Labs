#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
using namespace std;

// Custom exceptions
class IncompleteInfoException : public runtime_error
{
public:
    IncompleteInfoException() : runtime_error("Incomplete patient information!") {}
};

class InvalidPriorityException : public runtime_error
{
public:
    InvalidPriorityException() : runtime_error("Invalid derived priority!") {}
};

class DelayedServingException : public runtime_error
{
public:
    DelayedServingException() : runtime_error("Patient serving delayed!") {}
};

// Patient class
class Patient
{
    string name;
    int age;
    string condition;
    bool hasRef;  // Strong reference status
    int priority; // Lower number = higher priority

public:
    Patient() : name(""), age(0), condition(""), priority(5), hasRef(false) {}

    Patient(string name, int age, string condition, bool ref) : name(name), age(age), hasRef(ref)
    {
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

    // Function to update patient information
    void updateInfo(string name, int age, string condition, bool ref)
    {
        if (name.empty() || condition.empty() || age == 0)
        {
            throw IncompleteInfoException();
        }

        this->name = name;
        this->age = age;
        this->hasRef = ref;

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

    // Function to derive priority
    int derivePriority()
    {
        if (hasRef)
        {
            priority = 1;
        }
        else if (age >= 60)
        {
            priority = 2; // Senior citizens
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
            throw InvalidPriorityException();
        }
        return priority;
    }

    int getPriority() const { return priority; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getCondition() const { return condition; }
    bool isSenior() const { return age >= 60; }

    // Display patient info
    void display() const
    {
        cout << "Name: " << name << ", Age: " << age
             << ", Condition: " << condition << ", Priority: " << priority << endl;
    }
};

// Function to enqueue patients based on priority
void prioritizePatients(Patient p, queue<Patient> &highPriority, queue<Patient> &mediumPriority, queue<Patient> &lowPriority)
{
    int priority = p.getPriority();

    if (priority == 1 || priority == 2 || priority == 3)
    {
        highPriority.push(p); // High priority: strong reference, seniors, intense cases
    }
    else if (priority == 4)
    {
        mediumPriority.push(p); // Medium priority: critical cases
    }
    else
    {
        lowPriority.push(p); // Low priority: normal cases
    }
}

// Function to combine the queues based on priority
queue<Patient> combineQueues(queue<Patient> &highPriority, queue<Patient> &mediumPriority, queue<Patient> &lowPriority)
{
    queue<Patient> finalQueue;

    while (!highPriority.empty())
    {
        finalQueue.push(highPriority.front());
        highPriority.pop();
    }
    while (!mediumPriority.empty())
    {
        finalQueue.push(mediumPriority.front());
        mediumPriority.pop();
    }
    while (!lowPriority.empty())
    {
        finalQueue.push(lowPriority.front());
        lowPriority.pop();
    }

    return finalQueue;
}

// Function to display the current queue
void displayCurrentPatients(queue<Patient> highPriority, queue<Patient> mediumPriority, queue<Patient> lowPriority)
{
    cout << "\nHigh-priority patients:" << endl;
    if (highPriority.empty())
    {
        cout << "None" << endl;
    }
    else
    {
        while (!highPriority.empty())
        {
            highPriority.front().display();
            highPriority.pop();
        }
    }

    cout << "\nMedium-priority patients:" << endl;
    if (mediumPriority.empty())
    {
        cout << "None" << endl;
    }
    else
    {
        while (!mediumPriority.empty())
        {
            mediumPriority.front().display();
            mediumPriority.pop();
        }
    }

    cout << "\nLow-priority patients:" << endl;
    if (lowPriority.empty())
    {
        cout << "None" << endl;
    }
    else
    {
        while (!lowPriority.empty())
        {
            lowPriority.front().display();
            lowPriority.pop();
        }
    }
}

// Serve patients based on priority and ensure senior citizens are served after a max of 3 others
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
    queue<Patient> highPriority, mediumPriority, lowPriority;

    try
    {
        string name, condition;
        int age;
        bool hasRef;
        char option;
        do
        {
            cout << "\nMenu: \n1. Add a patient \n2. View current patients \n3. Serve patients \nEnter your choice: ";
            cin >> option;

            switch (option)
            {
            case '1':
            {
                // Add a patient
                cout << "Enter patient name: ";
                cin >> name;

                cout << "Enter patient age: ";
                cin >> age;

                cout << "Enter patient condition (Normal, Critical, Intense): ";
                cin >> condition;

                cout << "Does the patient have a strong reference? (1 for yes, 0 for no): ";
                cin >> hasRef;

                try
                {
                    Patient newPatient(name, age, condition, hasRef);
                    prioritizePatients(newPatient, highPriority, mediumPriority, lowPriority);
                    cout << "Patient added successfully!" << endl;
                }
                catch (const exception &e)
                {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
            case '2':
                displayCurrentPatients(highPriority, mediumPriority, lowPriority);
                break;

            case '3':
            {
                queue<Patient> finalQueue = combineQueues(highPriority, mediumPriority, lowPriority);
                cout << "Serving patients based on priority:" << endl;
                servePatients(finalQueue);
                break;
            }

            default:
                cout << "Invalid choice! Please enter 1, 2, or 3." << endl;
                break;
            }

            cout << "Do you want to continue? (y/n): ";
            cin >> option;

        } while (option == 'y' || option == 'Y');
    }
    catch (const IncompleteInfoException &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch (const InvalidPriorityException &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch (const DelayedServingException &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch (const invalid_argument &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
