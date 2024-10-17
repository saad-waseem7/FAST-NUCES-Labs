#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>

using namespace std;

struct student
{
    string name;
    int rollNo;
};

// Function to manage Hammad's exam submission and marking process
void manageExam(int totalStudents, student students[], int hammadRollNo)
{
    queue<student> submissionQueue; // Queue for submission
    stack<student> submissionStack; // Stack to manage the marking process
    stack<student> markedStack;     // Stack for marked exams

    int hammadPosition = -1;   // Position in submission queue
    int queueBeforeSubmit = 0; // Queue in front of submission desk (3% of total)
    int hammadSubmitStackPosition = -1;
    int hammadMarkPosition = -1;
    int hammadReceivePosition = -1;

    // Calculate the number of people who submitted before Hammad
    int studentsBeforeHammad = (69 * totalStudents) / 100;
    queueBeforeSubmit = (3 * totalStudents) / 100;

    // Fill the submission queue
    for (int i = 0; i < totalStudents; i++)
    {
        submissionQueue.push(students[i]);
        if (students[i].rollNo == hammadRollNo)
        {
            hammadPosition = i + 1; // Store Hammad's position in the queue
        }
    }

    cout << "1. Hammad received his exam after " << hammadPosition << " students." << endl;

    // Move students to submission stack and mark exams
    int count = 0;
    while (!submissionQueue.empty())
    {
        student currentStudent = submissionQueue.front();
        submissionQueue.pop();
        submissionStack.push(currentStudent); // Place in submission stack

        // Check if Hammad submitted at this point
        if (currentStudent.rollNo == hammadRollNo)
        {
            hammadSubmitStackPosition = submissionStack.size();
        }

        // Simulate marking process (top first)
        if (submissionStack.size() == studentsBeforeHammad + queueBeforeSubmit + 1)
        {
            cout << "2. Hammad submitted his exam after waiting for " << studentsBeforeHammad + queueBeforeSubmit << " students." << endl;
        }

        // Mark the exam by popping from the submission stack and pushing to the marked stack
        markedStack.push(submissionStack.top());
        submissionStack.pop();

        if (markedStack.top().rollNo == hammadRollNo)
        {
            hammadMarkPosition = count + 1; // Track Hammad's exam marking position
        }

        count++;
    }

    cout << "2. Hammad submitted his exam after waiting for " << studentsBeforeHammad + queueBeforeSubmit << " students." << endl;
    cout << "3. Hammad's exam was placed at position " << hammadSubmitStackPosition << " in the submission stack." << endl;
    cout << "4. Hammad's exam was marked at position " << hammadMarkPosition << " in the marking process." << endl;

    // Now simulate Hammad retrieving his exam (searching through the marked stack)
    stack<student> retrievalStack; // Temporary stack to help Hammad search his paper
    count = 0;
    bool found = false;

    while (!markedStack.empty())
    {
        student currentStudent = markedStack.top();
        markedStack.pop();
        retrievalStack.push(currentStudent);

        count++;

        if (currentStudent.rollNo == hammadRollNo)
        {
            hammadReceivePosition = count;
            found = true;
            break;
        }
    }

    cout << "5. Hammad's exam was placed at position " << hammadReceivePosition << " in the marked stack." << endl;

    // Maximum and minimum number of exams Hammad would have gone through
    int maxExamsToSearch = totalStudents;
    int minExamsToSearch = count;

    cout << "6. Hammad received his exam back after " << hammadReceivePosition << " students." << endl;
    cout << "7. Maximum number of exams Hammad would have been through while searching: " << maxExamsToSearch << endl;
    cout << "8. Minimum number of exams Hammad would have been through while searching: " << minExamsToSearch << endl;

    // Print final stacks and queues
    cout << "\n--- Final Stacks and Queues ---\n";
    cout << "Submission Stack (top to bottom): ";
    while (!submissionStack.empty())
    {
        cout << submissionStack.top().rollNo << " ";
        submissionStack.pop();
    }
    cout << endl;

    cout << "Marked Stack (top to bottom): ";
    while (!retrievalStack.empty())
    {
        cout << retrievalStack.top().rollNo << " ";
        retrievalStack.pop();
    }
    cout << endl;
}

// Function to read students from a file
int readStudentsFromFile(const string &fileName, student students[], int maxStudents)
{
    ifstream file(fileName);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << fileName << endl;
        return 0;
    }

    string line;
    int count = 0;

    // Read file line by line
    while (getline(file, line) && count < maxStudents)
    {
        stringstream ss(line);
        int rollNo;
        string name;

        // Parse roll number and name from the line
        if (ss >> rollNo && getline(ss, name, ','))
        {
            students[count].rollNo = rollNo; // Directly use the extracted integer roll number
            students[count].name = name;
            count++;
        }
    }

    file.close();
    return count;
}

int main()
{
    const int maxStudents = 200;   // Example: Maximum of 200 students
    student students[maxStudents]; // Array of students

    // Read students from the file "students.txt"
    int totalStudents = readStudentsFromFile("Data.txt", students, maxStudents);

    // Find Hammad's roll number (assuming it is 420)
    int hammadRollNo = 420;

    // Manage the exam for Hammad
    if (totalStudents > 0)
    {
        manageExam(totalStudents, students, hammadRollNo);
    }
    else
    {
        cout << "No students found in the file." << endl;
    }

    return 0;
}
