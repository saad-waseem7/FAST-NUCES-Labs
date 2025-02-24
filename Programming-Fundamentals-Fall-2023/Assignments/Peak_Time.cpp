#include<iostream>
using namespace std;

const int max_guests = 5;

bool is_valid(int t)
{
    return (t >= 9 && t <= 22);
}

void main_arrival(int arrival[], int max_guests)
{
    cout << "Enter Arrival Time Of Guests: "<<endl;
    for (int i = 0; i < max_guests; i++)
    {
        cout << "Guest " << i + 1 << ": ";
        cin >> arrival[i];

        while (!is_valid(arrival[i]))
        {
            cout << "Invalid arrival time. Please enter a time between 9 and 22: ";
            cin >> arrival[i];
        }
    }
}

void main_depart(int depart[], int max_guests)
{
    cout << "Enter Departure Time Of Guests: "<<endl;
    for (int i = 0; i < max_guests; i++)
    {
        cout << "Guest " << i + 1 << ": ";
        cin >> depart[i];

        while (!is_valid(depart[i]))
        {
            cout << "Invalid departure time. Please enter a time between 9 and 22: ";
            cin >> depart[i];
        }
    }
}

void peak_time(int arrival[], int depart[], int max_guests)
{
    int max_t = 0;
    int current_most = 0;
    int current_most2 = 0;

    for (int i = 0; i < max_guests; i++)
    {
        int current_occurrence = 0;

        for (int j = 0; j < max_guests; j++)
        {
            if (arrival[i] == arrival[j])
            {
                current_occurrence++;
            }
        }

        if (current_occurrence > current_most)
        {
            current_most = current_occurrence;
            max_t = arrival[i];
        }
    }

    for (int i = 0; i < max_guests; i++)
    {
        int current_occurrence = 0;

        for (int j = 0; j < max_guests; j++)
        {
            if (depart[i] == depart[j])
            {
                current_occurrence++;
            }
        }

        if (current_occurrence > current_most2)
        {
            current_most2 = current_occurrence;
            max_t = depart[i];
        }
    }

    cout << "Peak time: " << max_t << " with occurrences: " << current_most + current_most2 << endl;
}

int main()
{
    int arrival[max_guests] = {0};
    int depart[max_guests] = {0};

    main_arrival(arrival, max_guests);
    main_depart(depart, max_guests);

    peak_time(arrival, depart, max_guests);

    /*
    cout << "Entered Arrival Times: ";
    for (int i = 0; i < max_guests; i++)
    {
        cout << arrival[i] << " ";
    }
    cout << endl;

    cout << "Entered Departure Times: ";
    for (int i = 0; i < max_guests; i++)
    {
        cout << depart[i] << " ";
    }
    cout << endl;
    */
    
    return 0;
}
