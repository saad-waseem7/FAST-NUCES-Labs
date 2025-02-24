#include <iostream>
#include <fstream>
using namespace std;
int main() {
    ifstream inputFile("Numbers.txt");
    ofstream oddFile("odd.txt");
    ofstream evenFile("even.txt");
    int number;
    int oddCount = 0;
    int evenCount = 0;
    while (inputFile >> number) {
        if (number % 2 == 0) {
            evenFile << number << endl;
            evenCount++;
        }
        else {
            oddFile << number << endl;
            oddCount++;
        }
    }
    inputFile.close();
    oddFile.close();
    evenFile.close();
    cout << "Number of odd numbers: " << oddCount << endl;
    cout << "Number of even numbers: " << evenCount << endl;

    return 0;
}
