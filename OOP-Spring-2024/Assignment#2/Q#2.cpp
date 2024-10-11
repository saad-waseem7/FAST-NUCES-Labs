#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
using namespace std;

class CustomString
{
private:
  char *str;
  int len;

public:
  CustomString(const char *s = "");
  CustomString(const CustomString &s);
  ~CustomString();

  int length() const;
  void upper();
  void lower();
  char at(int index) const;
  CustomString substring(int start, int end) const;
  int compare(const CustomString &s) const;
  const char *get_data() const;
  CustomString operator+(const CustomString &s) const; // Concatenation
  CustomString &operator=(const CustomString &s);
  friend ostream &operator<<(ostream &os, const CustomString &s);
  friend istream &operator>>(istream &is, CustomString &s);
  friend bool operator==(const CustomString &s1, const CustomString &s2);
  friend bool operator!=(const CustomString &s1, const CustomString &s2);
  friend bool operator<(const CustomString &s1, const CustomString &s2);
  friend bool operator>(const CustomString &s1, const CustomString &s2);
};

CustomString::CustomString(const char *s)
{
  len = strlen(s);
  str = new char[len + 1];
  strcpy(str, s);
}

CustomString::CustomString(const CustomString &s)
{
  len = s.len;
  str = new char[len + 1];
  strcpy(str, s.str);
}

CustomString::~CustomString()
{
  // cout << "Destructor called" << endl;
  delete[] str;
}

int CustomString::length() const
{
  return len;
}

void CustomString::upper()
{
  if (str == nullptr)
  {
    cout << "Error: String is null." << endl;
    return;
  }

  bool needConversion = false;
  for (int i = 0; i < len; ++i)
  {
    if (*(str + i) >= 'a' && *(str + i) <= 'z')
    {
      needConversion = true;
      break;
    }
  }

  if (!needConversion)
  {
    cout << "String is already in uppercase." << endl;
    return;
  }

  for (int i = 0; i < len; ++i)
  {
    if (*(str + i) >= 'a' && *(str + i) <= 'z')
    {
      *(str + i) -= 32;
    }
  }
}

void CustomString::lower()
{
  if (str == nullptr)
  {
    cout << "Error: String is null." << endl;
    return;
  }

  bool needConversion = false;
  for (int i = 0; i < len; ++i)
  {
    if (*(str + i) >= 'A' && *(str + i) <= 'Z')
    {
      needConversion = true;
      break;
    }
  }

  if (!needConversion)
  {
    cout << "String is already in lowercase." << endl;
    return;
  }

  for (int i = 0; i < len; ++i)
  {
    if (*(str + i) >= 'A' && *(str + i) <= 'Z')
    {
      *(str + i) += 32;
    }
  }
}

char CustomString::at(int index) const
{
  if (index >= 0 && index < len)
  {
    return *(str + index);
  }
  else
  {
    return '\0';
  }
}

CustomString CustomString::substring(int start, int end) const
{
  if (start >= 0 && start < len && end >= start && end < len)
  {
    char *sub = new char[end - start + 2];
    strncpy(sub, str + start, end - start + 1);
    *(sub + (end - start + 1)) = '\0';
    CustomString substring(sub);
    delete[] sub;
    return substring;
  }
  else
  {
    return CustomString();
  }
}

int CustomString::compare(const CustomString &s) const
{
  return strcmp(str, s.str);
}

const char *CustomString::get_data() const
{
  return str;
}

ostream &operator<<(ostream &os, const CustomString &s)
{
  os << s.str;
  return os;
}

istream &operator>>(istream &is, CustomString &s)
{
  char input[100];
  is.getline(input, 100);
  s = CustomString(input);
  return is;
}

CustomString CustomString::operator+(const CustomString &s) const
{
  CustomString result;
  result.len = len + s.len;
  result.str = new char[result.len + 1];
  strcpy(result.str, str);
  strcat(result.str, s.str);
  return result;
}

CustomString &CustomString::operator=(const CustomString &s)
{
  if (this != &s)
  {
    delete[] str;

    len = s.len;
    str = new char[len + 1];
    strcpy(str, s.str);
  }
  return *this;
}

bool operator==(const CustomString &s1, const CustomString &s2)
{
  if (strcmp(s1.str, s2.str) == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool operator!=(const CustomString &s1, const CustomString &s2)
{
  if (strcmp(s1.str, s2.str) != 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool operator<(const CustomString &s1, const CustomString &s2)
{
  if (strcmp(s1.str, s2.str) < 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool operator>(const CustomString &s1, const CustomString &s2)
{
  if (strcmp(s1.str, s2.str) > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void printString(const CustomString &s, const string &message = "")
{
  if (!message.empty())
  {
    cout << message << ": ";
  }
  cout << s << endl;
}
int findSubstringIndex(const CustomString &s, const CustomString &substring)
{
  const char *str = s.get_data();
  const char *sub = substring.get_data();
  const char *pos = strstr(str, sub);
  if (pos != nullptr)
  {
    return pos - str;
  }
  else
  {
    return -1;
  }
}

int getValidIndexInput(const string &prompt, int minIndex, int maxIndex)
{
  int index;
  while (true)
  {
    cout << prompt;
    cin >> index;

    if (index < minIndex || index > maxIndex)
    {
      cout << "Invalid input! Please enter an integer between " << minIndex << " and " << maxIndex << "." << endl;
      cin.clear();
      cin.ignore();
    }
    else
    {
      break;
    }
  }
  return index;
}

bool compareStrings(const string &sen_1, const string &sen_2)
{
  if (sen_1 == sen_2)
  {
    return true;
  }
  else
  {
    return false;
  }
}

string getValidStringInput(const string &prompt)
{
  string input;
  bool validInput = false;
  cout << prompt;
  while (!validInput)
  {
    getline(cin, input);

    if (!input.empty())
    {
      validInput = true;
    }
    else
    {
      // cout << "String cannot be empty. Please enter a valid string." << endl;
    }
  }

  return input;
}

int main()
{
  const int maxLength = 100;
  char input[maxLength];

  while (true)
  {
    cout << "Enter a String: ";
    cin.getline(input, maxLength);

    bool validInput = true;
    int i = 0;
    while (input[i] != '\0')
    {
      if (!isalpha(input[i]) && !isspace(input[i]))
      {
        validInput = false;
        break;
      }
      ++i;
    }

    if (validInput)
    {
      break;
    }
    else
    {
      cout << "Invalid input! Please enter a string containing only alphabetic characters." << endl;
    }
  }

  cout << "You entered: " << input << endl;

  CustomString s(input);
  printString(s, "Original");
  cout << "Length: " << s.length() << endl;

  s.upper();
  printString(s, "Uppercase");

  s.lower();
  printString(s, "Lowercase");

  int k;
  bool validIndex = false;
  while (!validIndex)
  {
    while (true)
    {
      cout << "Enter index to find a Specific Character: ";
      cin >> k;
      if (k <= 0)
      {
        cout << "Invalid input! Please enter a positive integer." << endl;
        cin.clear();
        cin.ignore();
      }
      else
      {
        break;
      }
    }
    if (k >= 0 && k < s.length())
    {
      validIndex = true;
    }
    else
    {
      cout << "Error: Invalid index. Please enter a valid index." << endl;
      cin.clear();
    }
  }
  cout << "Character at index " << k << " : " << s.at(k) << endl;

  int start, end;
  cout << "Extraction of String using Start and End Index" << endl;

  start = getValidIndexInput("Enter start index: ", 0, s.length());
  end = getValidIndexInput("Enter end index: ", start, s.length());

  bool validRange = false;
  while (!validRange)
  {
    if (start >= 0 && start < s.length() && end >= start && end < s.length())
    {
      validRange = true;
    }
    else
    {
      cout << "Error: Invalid indices. Please enter valid indices." << endl;
      cin.clear();
    }
  }
  CustomString sub = s.substring(start, end);
  cout << "Substring from index " << start << " to " << end << ": " << sub << endl;

  string search;
  bool validSubstring = false;
  while (!validSubstring)
  {
    cout << "Enter substring to search: ";
    cin >> search;
    if (!search.empty())
    {
      bool validInput = true;
      char c;
      for (int i = 0; i < search.size(); ++i)
      {
        c = search[i];
        if (!isalpha(c))
        {
          validInput = false;
          break;
        }
      }

      if (validInput)
      {
        validSubstring = true;
      }
      else
      {
        cout << "Error: Substring should contain only alphabetic characters" << endl;
      }
    }
    else
    {
      cout << "Error: Please enter a non-empty substring" << endl;
    }
    cin.clear();
  }

  CustomString searchStr(search.c_str());
  int idx;
  idx = findSubstringIndex(s, searchStr);
  if (idx != -1)
  {
    cout << "Substring found at index: " << idx << endl;
  }
  else
  {
    cout << "Substring not found" << endl;
  }

  cout << "Do You Want to Compare Two Strings?\n";
  char choice;

  bool validChoice = false;
  while (!validChoice)
  {
    cin >> choice;
    if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N')
    {
      validChoice = true;
    }
    else
    {
      cout << "Invalid choice. Please enter 'y' or 'n': ";
    }
  }

  if (choice == 'y' || choice == 'Y')
  {
    cout << "Enter two strings you want to compare: " << endl;
    string sen_1 = getValidStringInput("String 1 = ");
    string sen_2 = getValidStringInput("String 2 = ");

    if (compareStrings(sen_1, sen_2))
    {
      cout << "Both strings are equal." << endl;
    }
    else
    {
      cout << "Strings are not equal." << endl;
    }
  }
  else if (choice == 'n' || choice == 'N')
  {
    cout << "Exiting..." << endl;
  }

  return 0;
}