#include <iostream>
using namespace std;

void correctString(char str[]) {
	int index = 0;

	while (str[index] != '\0') {
		if (str[index] >= 'a' && str[index] <= 'z') {
			str[index] -= 32;
		}
		if ((str[index] < 'A' || str[index] > 'Z') && (str[index] < 'a' || str[index] > 'z')) {
			for (int j = index; j < strlen(str); j++) {
				str[j] = str[j + 1];
			}
			continue;
		}
		if (str[index] == ' ') {
			for (int j = index; j < strlen(str); j++) {
				str[j] = str[j + 1];
			}
			continue;
		}
		index++;
	}
}
int main() {
	char str[100];
	cout << "Enter String: ";
	cin >> str;
	correctString(str);
	cout << str << endl;
	return 0;
}
