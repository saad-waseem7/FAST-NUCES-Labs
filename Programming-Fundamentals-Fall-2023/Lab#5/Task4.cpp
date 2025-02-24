#include <iostream>
#include <cstring>
using namespace std;
bool isRotation(const char strA[], const char strB[]) {
    int lengthA = strlen(strA);
    int lengthB = strlen(strB);
    if (lengthA != lengthB) {
        return false;
    }
    if (lengthA == 0 || lengthB == 0) {
        return strcmp(strA, strB) == 0;
    }
    char concatenated[2 * lengthA + 1];
    strcpy(concatenated, strA);
    strcat(concatenated, strA);
    if (strstr(concatenated, strB) != 0) {
        return true;
    }
    return false;
}
int main() {
    const char stringA[] = "HELLO";
    const char stringB[] = "LOHEL";

    if (isRotation(stringA, stringB)) {
        cout << "The strings are rotations of each other." << endl;
    }
    else {
        cout << "The strings are not rotations of each other." << endl;
    }
    return 0;
}
