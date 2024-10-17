#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>

using namespace std;

struct student
{
    string name;
    int roll;
};

void Exam_Hall(int totalStudents, student students[], int hammad_roll)
{
    queue<student> queue_for_submission;
    stack<student> stack_for_submission;
    stack<student> stack_for_marked;

    int hammad_pos = -1;
    int queue_before_submission = 0;
    int hammad_submit_pos_stack = -1;
    int hammad_marked_position = -1;
    int hammad_receive_position = -1;

    int studentsBeforeHammad = (69 * totalStudents) / 100;
    queue_before_submission = (3 * totalStudents) / 100;

    for (int i = 0; i < totalStudents; i++)
    {
        queue_for_submission.push(students[i]);
        if (students[i].roll == hammad_roll)
        {
            hammad_pos = i + 1;
        }
    }

    cout << "1. Hammad received his exam after " << hammad_pos << " students." << endl;

    int count = 0;
    while (!queue_for_submission.empty())
    {
        student currentStudent = queue_for_submission.front();
        queue_for_submission.pop();
        stack_for_submission.push(currentStudent);

        if (currentStudent.roll == hammad_roll)
        {
            hammad_submit_pos_stack = stack_for_submission.size();
        }

        if (stack_for_submission.size() == studentsBeforeHammad + queue_before_submission + 1)
        {
            cout << "2. Hammad submitted his exam after waiting for " << studentsBeforeHammad + queue_before_submission << " students." << endl;
        }

        stack_for_marked.push(stack_for_submission.top());
        stack_for_submission.pop();

        if (stack_for_marked.top().roll == hammad_roll)
        {
            hammad_marked_position = count + 1;
        }

        count++;
    }

    cout << "2. Hammad submitted his exam after waiting for " << studentsBeforeHammad + queue_before_submission << " students." << endl;
    cout << "3. Hammad's exam was placed at position " << hammad_submit_pos_stack << " in the submission stack." << endl;
    cout << "4. Hammad's exam was marked at position " << hammad_marked_position << " in the marking process." << endl;

    stack<student> retrieved_data_stack;
    count = 0;
    bool found = false;

    while (!stack_for_marked.empty())
    {
        student currentStudent = stack_for_marked.top();
        stack_for_marked.pop();
        retrieved_data_stack.push(currentStudent);

        count++;

        if (currentStudent.roll == hammad_roll)
        {
            hammad_receive_position = count;
            found = true;
            break;
        }
    }

    cout << "5. Hammad's exam was placed at position " << hammad_receive_position << " in the marked stack." << endl;

    int maxExamsToSearch = totalStudents;
    int minExamsToSearch = count;

    cout << "6. Hammad received his exam back after " << hammad_receive_position << " students." << endl;
    cout << "7. Maximum number of exams Hammad would have been through while searching: " << maxExamsToSearch << endl;
    cout << "8. Minimum number of exams Hammad would have been through while searching: " << minExamsToSearch << endl;

    cout << "\n--- Stacks & Queues after performing operations---\n";
    cout << "Submission Stack (top to bottom): ";
    while (!stack_for_submission.empty())
    {
        cout << stack_for_submission.top().roll << " ";
        stack_for_submission.pop();
    }
    cout << endl;

    cout << "Marked Stack (top to bottom): ";
    while (!retrieved_data_stack.empty())
    {
        cout << retrieved_data_stack.top().roll << " ";
        retrieved_data_stack.pop();
    }
    cout << endl;
}

int read_data_from_file(const string &fileName, student students[], int student_max)
{
    ifstream file(fileName);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << fileName << endl;
        return 0;
    }

    string line;
    int count = 0;

    while (getline(file, line) && count < student_max)
    {
        stringstream ss(line);
        int roll;
        string name;

        if (ss >> roll && getline(ss, name, ','))
        {
            students[count].roll = roll;
            students[count].name = name;
            count++;
        }
    }

    file.close();
    return count;
}

int main()
{
    const int student_max = 200;
    student students[student_max];

    int totalStudents = read_data_from_file("Data.txt", students, student_max);

    int hammad_roll = 420;

    if (totalStudents > 0)
    {
        Exam_Hall(totalStudents, students, hammad_roll);
    }
    else
    {
        cout << "No students found in the file." << endl;
    }

    return 0;
}
