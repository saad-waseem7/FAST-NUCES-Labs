#include <iostream>
using namespace std;
int main() {
    float litersUsed, kilometersDriven, consumption;
    float totalLitersUsed = 0;
    float totalKilometersDriven = 0;
    float overallAverageConsumption;
    cout << "Enter the liters used (-1 to end): ";
    cin >> litersUsed;
    while (litersUsed != -1) {
        cout << "Enter the kilometers driven: ";
        cin >> kilometersDriven;
        consumption = litersUsed / (kilometersDriven / 100);
        cout << "The liters/100km for this tank was " << consumption << endl;
        totalLitersUsed = totalLitersUsed + litersUsed;
        totalKilometersDriven = totalKilometersDriven + kilometersDriven;
        cout << "Enter the liters used (-1 to end): ";
        cin >> litersUsed;
    }
    overallAverageConsumption = totalLitersUsed / (totalKilometersDriven / 100);
    cout << "The overall average consumption was: " << overallAverageConsumption << endl;
    return 0;
}
