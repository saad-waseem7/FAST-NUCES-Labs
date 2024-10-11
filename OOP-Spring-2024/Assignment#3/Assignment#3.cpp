#include <iostream>
#include <string>
#include <cctype>
#include <Windows.h>
using namespace std;
class Book
{
private:
    string title;
    string author;
    string publisher;
    string ISBN;
    bool availability;
    int quantity;

public:
    Book();
    void SetTitle(const string &title);
    void SetAuthor(const string &author);
    void SetPublisher(const string &publisher);
    void SetIsbn(const string &ISBN);
    void SetAvailability(bool availability);
    void SetQuantity(int quantity);
    const string &GetTitle() const;
    const string &GetAuthor() const;
    const string &GetIsbn() const;
    const string &GetPublisher() const;
    bool GetAvailability() const;
    int GetQuantity() const;
    void DisplayBookDetails() const;
    ~Book();
};
Book::Book()
{
    this->availability = true;
    this->quantity = 0;
}

void Book::SetTitle(const string &title)
{
    this->title = title;
}
void Book::SetAuthor(const string &author)
{
    this->author = author;
}
void Book::SetPublisher(const string &publisher)
{
    this->publisher = publisher;
}
void Book::SetIsbn(const string &ISBN)
{
    this->ISBN = ISBN;
}
void Book::SetAvailability(bool availability)
{
    this->availability = availability;
}
void Book::SetQuantity(int quantity)
{
    this->quantity = quantity;
}
const string &Book::GetTitle() const
{
    return this->title;
}
const string &Book::GetAuthor() const
{
    return this->author;
}
const string &Book::GetIsbn() const
{
    return this->ISBN;
}
const string &Book::GetPublisher() const
{
    return this->publisher;
}
bool Book::GetAvailability() const
{
    return this->availability;
}

int Book::GetQuantity() const
{
    return this->quantity;
}
void Book::DisplayBookDetails() const
{
    cout << "Title: " << this->title << endl;
    cout << "Author: " << this->author << endl;
    cout << "Publisher: " << this->publisher << endl;
    cout << "ISBN: " << this->ISBN << endl;
    cout << "Quantity: " << this->quantity << endl;
    if (availability)
    {
        cout << "The book is available" << endl;
    }
    if (!availability)
    {
        cout << "The book is not available" << endl;
    }
    cout << "The quantity available is " << this->quantity << endl;
}
Book::~Book()
{
    // cout << "The book is deleted" << endl;
}

class Library
{
private:
    static const int MAX = 100;
    Book books[MAX];
    int numBooks;
    int Quantity;

public:
    Library();
    void AddBook(const Book &book);
    void RemoveBook(const string &isbn);
    void SearchBook(const string &keyword) const;
    const Book &getBook(int index) const;
    int getNumBooks() const;
    void displayAvailableBooks() const;
    ~Library();
};
Library::Library()
{
    this->numBooks = 0;
    this->Quantity = 0;
}

void Library::AddBook(const Book &book)
{
    if (numBooks < MAX)
    {
        books[numBooks] = book;
        numBooks++;
    }
    else
    {
        cout << "Library is full. Cannot add more books." << endl;
    }
}

void Library::RemoveBook(const string &isbn)
{
    int i = 0;
    bool found = false;
    while (i < numBooks)
    {
        if (books[i].GetIsbn() == isbn)
        {
            found = true;
            break;
        }
        i++;
    }

    if (found)
    {

        for (int j = i; j < numBooks - 1; ++j)
        {
            books[j] = books[j + 1];
        }
        numBooks--;
        cout << "Book with ISBN " << isbn << " removed from the library." << endl;
    }
    else
    {
        cout << "Book with ISBN " << isbn << " not found in the library." << endl;
    }
}

void Library::SearchBook(const string &keyword) const
{
    bool found = false;
    int i = 0;
    while (i < numBooks)
    {
        const Book &book = books[i];
        if (book.GetIsbn() == keyword || book.GetAuthor() == keyword || book.GetTitle() == keyword)
        {
            book.DisplayBookDetails();
            found = true;
        }
        i++;
    }
    if (!found)
    {
        cout << "No results found." << endl;
    }
}
const Book &Library::getBook(int index) const
{
    return books[index];
}
int Library::getNumBooks() const
{
    return this->numBooks;
}

void Library::displayAvailableBooks() const
{
    bool found = false;
    int i = 0;
    while (i < numBooks)
    {
        const Book &book = books[i];
        if (book.GetAvailability())
        {
            book.DisplayBookDetails();
            found = true;
        }
        i++;
    }

    if (!found)
    {
        cout << "No available books in the library" << endl;
    }
}

Library::~Library()
{
    // cout << "The library is deleted" << endl;
}

class Member
{
private:
    string name;
    int id;
    Book *booksCheckedOut[5];

public:
    Member();
    Member(const string &name, int id);
    void setName(const string &name);
    string getName() const;
    void setId(int id);
    int getId() const;
    bool checkOutBook(Book *book);
    bool returnBook(Book *book);
    void displayCheckedOutBooks() const;
    ~Member();
};

Member::Member()
{
    this->id = 0;
    this->name = "";
    for (int i = 0; i < 5; i++)
    {
        this->booksCheckedOut[i] = nullptr;
    }
    // cout << "The member is created" << endl;
}

Member::Member(const string &name, int id)
{
    this->name = name;
    this->id = id;
    for (int i = 0; i < 5; ++i)
    {
        *(booksCheckedOut + i) = nullptr;
    }
}

void Member::setName(const string &name)
{
    this->name = name;
}

string Member::getName() const
{
    return this->name;
}

void Member::setId(int id)
{
    this->id = id;
}

int Member::getId() const
{
    return this->id;
}

bool Member::checkOutBook(Book *book)
{
    for (int i = 0; i < 5; ++i)
    {
        if ((*(booksCheckedOut + i)) == nullptr)
        {
            *(booksCheckedOut + i) = book;
            int currentQuantity = book->GetQuantity();
            if (currentQuantity > 0)
            {
                book->SetQuantity(currentQuantity - 1);
            }
            book->SetAvailability(false);
            return true;
        }
    }
    return false;
}

bool Member::returnBook(Book *book)
{
    for (int i = 0; i < 5; ++i)
    {
        if ((*(booksCheckedOut + i)) == book)
        {
            *(booksCheckedOut + i) = nullptr;
            int currentQuantity = book->GetQuantity();
            book->SetQuantity(currentQuantity + 1);
            book->SetAvailability(true);
        }
    }
    return false;
}

void Member::displayCheckedOutBooks() const
{
    cout << "Books checked out by " << name << " (ID: " << id << "):\n";
    for (int i = 0; i < 5; ++i)
    {
        if ((*(booksCheckedOut + i)) != nullptr)
        {
            cout << "Title: " << (*(booksCheckedOut + i))->GetTitle();
            cout << ", Author: " << (*(booksCheckedOut + i))->GetAuthor();
            cout << ", ISBN: " << (*(booksCheckedOut + i))->GetIsbn();
            cout << ", Publisher: " << (*(booksCheckedOut + i))->GetPublisher() << endl;
        }
    }
}

Member::~Member()
{
    // cout << "The member is deleted" << endl;
    for (int i = 0; i < 5; ++i)
    {
        *(booksCheckedOut + i) = nullptr;
    }
}

void addBook(Library &library);
void removeBook(Library &library);
void searchBook(Library &library);
void checkoutBook(Library &library);
void addMember(Member members[], int &numMembers);
void removeMember(Member members[], int &numMembers, int memberId);
void searchMember(const Member members[], int numMembers, int memberId);
void manageMembers(Member members[], int &numMembers);

void addBook(Library &library)
{
    cout << "Enter book details:" << endl;
    Book book;
    string title, author, publisher, isbn;
    int quantity;

    cout << "Enter Title: ";
    while (true)
    {
        getline(cin, title);
        bool valid = true;
        for (char c : title)
        {
            if (!isalpha(c) && !isspace(c))
            {
                valid = false;
                break;
            }
        }
        if (!title.empty() && valid)
        {
            book.SetTitle(title);
            break;
        }
        // cout << "Error: Title must contain alphabetic characters only." << endl;
    }

    cout << "Enter Author: ";
    while (true)
    {
        getline(cin, author);
        bool valid = true;
        for (char c : author)
        {
            if (!isalpha(c) && !isspace(c))
            {
                valid = false;
                break;
            }
        }
        if (!author.empty() && valid)
        {
            book.SetAuthor(author);
            break;
        }
        cout << "Error: Author must contain alphabetic characters only." << endl;
    }

    cout << "Enter Publisher: ";
    while (true)
    {
        getline(cin, publisher);
        bool valid = true;
        for (char c : publisher)
        {
            if (!isalpha(c) && !isspace(c))
            {
                valid = false;
                break;
            }
        }
        if (!publisher.empty() && valid)
        {
            book.SetPublisher(publisher);
            break;
        }
        cout << "Error: Publisher must contain alphabetic characters only." << endl;
    }

    cout << "Enter ISBN: ";
    while (true)
    {
        getline(cin, isbn);
        bool valid = true;
        for (char c : isbn)
        {
            if (!isdigit(c))
            {
                valid = false;
                break;
            }
        }
        if (!isbn.empty() && valid)
        {
            book.SetIsbn(isbn);
            break;
        }
        cout << "Error: ISBN must contain numeric characters only." << endl;
    }

    cout << "Enter the quantity of the books to add: ";
    while (true)
    {
        cin >> quantity;
        if (quantity > 0 && quantity < 1000)
        {
            break;
        }
        cout << "Error: Quantity must be a positive integer." << endl;
        cin.clear();
        cin.ignore();
    }
    book.SetQuantity(quantity);

    library.AddBook(book);
}

void removeBook(Library &library)
{
    string isbn;
    cout << "Enter ISBN of the book to remove from library: ";
    while (true)
    {
        cin >> isbn;
        bool isValid = true;
        for (char c : isbn)
        {
            if (!isdigit(c))
            {
                isValid = false;
                break;
            }
        }
        if (!isbn.empty() && isValid)
        {
            break;
        }
        cout << "Error: ISBN must contain numeric characters only. Please enter again: ";
        cin.clear();
        cin.ignore();
    }

    int index = -1;
    for (int i = 0; i < library.getNumBooks(); ++i)
    {
        if (library.getBook(i).GetIsbn() == isbn)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        Book &bookToRemove = const_cast<Book &>(library.getBook(index));

        int currentQuantity = bookToRemove.GetQuantity();
        if (currentQuantity > 1)
        {
            bookToRemove.SetQuantity(currentQuantity - 1);
        }
        else
        {
            library.RemoveBook(isbn);
        }
    }
    else
    {
        cout << "Book with ISBN " << isbn << " not found in the library." << endl;
    }
}

void searchBook(Library &library)
{
    string keyword;
    cout << "Enter keyword (Title, Author, ISBN, Publisher) to search: ";

    cin.ignore();

    while (true)
    {
        getline(cin, keyword);

        if (!keyword.empty())
        {
            break;
        }
        cout << "Error: Keyword cannot be empty. Please enter again: ";
    }

    library.SearchBook(keyword);
}

void checkoutBook(Library &library)
{
    int memberId;

    cout << "Enter your member ID: ";
    while (true)
    {
        cin >> memberId;
        if (memberId > 0 && memberId < 99999)
        {
            break;
        }
        else
        {
            cout << "Error: Invalid member ID. Please enter a positive integer." << endl;
            cin.clear();
            cin.ignore();
        }
    }

    string isbn;
    // cout << "Enter ISBN of the book to remove from library: ";
    cout << "Enter ISBN of the book to checkout from library: ";
    while (true)
    {
        cin >> isbn;
        bool isValid = true;
        for (char c : isbn)
        {
            if (!isdigit(c))
            {
                isValid = false;
                break;
            }
        }
        if (!isbn.empty() && isValid)
        {
            break;
        }
        cout << "Error: ISBN must contain numeric characters only. Please enter again: ";
        cin.clear();
        cin.ignore();
    }

    int index = -1;
    for (int i = 0; i < library.getNumBooks(); ++i)
    {
        if (library.getBook(i).GetIsbn() == isbn)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        Book &bookToRemove = const_cast<Book &>(library.getBook(index));

        int currentQuantity = bookToRemove.GetQuantity();
        if (currentQuantity > 1)
        {
            bookToRemove.SetQuantity(currentQuantity - 1);
        }
        else
        {
            library.RemoveBook(isbn);
            cout << "Book with ISBN " << isbn << " checked out from library." << endl;
        }
    }
    else
    {
        cout << "Book with ISBN " << isbn << " not found in the library." << endl;
    }
}

void addMember(Member members[], int &numMembers)
{
    if (numMembers >= 100)
    {
        cout << "Maximum number of members reached. Cannot add more members." << endl;
        return;
    }

    int memberId;
    string name;

    cout << "Enter your member ID: ";
    while (true)
    {
        cin >> memberId;
        if (memberId > 0 && memberId < 99999)
        {
            break;
        }
        else
        {
            cout << "Error: Invalid member ID. Please enter a positive integer." << endl;
            cin.clear();
            cin.ignore();
        }
    }

    while (true)
    {
        cout << "Enter name of Member: ";
        cin >> name;
        bool valid = true;
        for (char c : name)
        {
            if (!isalpha(c))
            {
                valid = false;
                break;
            }
        }
        if (!name.empty() && valid)
        {
            break;
        }
        cout << "Error: Name must contain alphabetic characters only. Please enter again: ";
    }

    members[numMembers] = Member(name, memberId);
    numMembers++;

    cout << "Member added successfully." << endl;
}

void removeMember(Member members[], int &numMembers, int memberId)
{
    int index = -1;
    for (int i = 0; i < numMembers; ++i)
    {
        if (members[i].getId() == memberId)
        {
            index = i;
            break;
        }
    }

    if (index != -1)
    {
        for (int i = index; i < numMembers - 1; ++i)
        {
            members[i] = members[i + 1];
        }
        numMembers--;
        cout << "Member with ID " << memberId << " removed successfully." << endl;
    }
    else
    {
        cout << "Member with ID " << memberId << " not found." << endl;
    }
}

void searchMember(const Member members[], int numMembers, int memberId)
{
    bool found = false;
    for (int i = 0; i < numMembers; ++i)
    {
        if (members[i].getId() == memberId)
        {
            cout << "Member found:" << endl;
            cout << "Name: " << members[i].getName() << endl;
            cout << "ID: " << members[i].getId() << endl;
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Member with ID " << memberId << " not found." << endl;
    }
}

void manageMembers(Member members[], int &numMembers)
{
    int choice = 0;
    while (choice != 4)
    {
        cout << "\n==========================================" << endl;
        cout << "|\t                              \t |" << endl;
        cout << "|\t      \"Manage Members\"      \t |" << endl;
        cout << "|\t                              \t |" << endl;
        cout << "==========================================" << endl;
        cout << "|\t1. Add a member            \t |" << endl;
        cout << "|\t2. Remove a member         \t |" << endl;
        cout << "|\t3. Search for a member     \t |" << endl;
        cout << "|\t4. Back to Main Menu       \t |" << endl;
        cout << "==========================================" << endl;
        string input;
        bool inputIsValid;

        do
        {
            cout << "\nEnter your choice: ";
            cin >> input;

            inputIsValid = true;

            for (char c : input)
            {
                if (!isdigit(c))
                {
                    inputIsValid = false;
                    break;
                }
            }

            if (!inputIsValid)
            {
                cout << "Error: Please enter a numeric value.\n";
            }
            else
            {

                choice = stoi(input);
            }
        } while (!inputIsValid);

        while (true)
        {
            if (!(choice == 1 || choice == 2 || choice == 3 || choice == 4))
            {
                cout << "Error: Invalid choice. Please enter again: ";
                cin >> choice;
            }
            else
            {
                break;
            }
        }

        cout << endl;

        switch (choice)
        {
        case 1:
            system("cls");
            addMember(members, numMembers);
            break;
        case 2:
            system("cls");
            int memberIdToRemove;
            cout << "Enter the ID of the member to remove: ";
            while (true)
            {
                cin >> memberIdToRemove;
                if (cin.good() && (memberIdToRemove > 99999 && memberIdToRemove < 0))
                {
                    break;
                }
                cout << "Error: Invalid input. Please enter a valid member ID: ";
                cin.clear();
                cin.ignore();
            }
            removeMember(members, numMembers, memberIdToRemove);
            break;
        case 3:
            system("cls");
            int memberIdToSearch;
            cout << "Enter the ID of the member to search: ";

            while ((!(cin >> memberIdToSearch)) || (memberIdToSearch > 99999 && memberIdToSearch < 0))
            {
                cin.clear();
                cin.ignore();
            }
            searchMember(members, numMembers, memberIdToSearch);
            break;
        case 4:
            system("cls");
            cout << "\n>>>Returning to Main Menu...Please Wait..\n";
            cout << endl;
            Sleep(2000);
            system("cls");
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
            break;
        }
        cout << endl;
    }
}

int main()
{
    Library library;
    Member members[100];
    int numMembers = 0;
    int choice = 0;
    while (choice != 7)
    {
        cout << "\n==========================================" << endl;
        cout << "|\t                              \t |" << endl;
        cout << "|\t\"Library Management System\" \t |" << endl;
        cout << "|\t                              \t |" << endl;
        cout << "==========================================" << endl;
        cout << "|\t1. Add a book              \t |" << endl;
        cout << "|\t2. Remove a book           \t |" << endl;
        cout << "|\t3. Search for a book       \t |" << endl;
        cout << "|\t4. Display available books \t |" << endl;
        cout << "|\t5. Checkout a book         \t |" << endl;
        cout << "|\t6. Manage Members          \t |" << endl;
        cout << "|\t7. Exit                    \t |" << endl;
        cout << "==========================================" << endl;
        string input;
        bool inputIsValid;

        do
        {
            cout << "\nEnter your choice: ";
            cin >> input;

            inputIsValid = true;

            for (char c : input)
            {
                if (!isdigit(c))
                {
                    inputIsValid = false;
                    break;
                }
            }

            if (!inputIsValid)
            {
                cout << "Error: Please enter a numeric value.\n";
            }
            else
            {

                choice = stoi(input);
            }
        } while (!inputIsValid);

        while (true)
        {
            if (!(choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 7))
            {
                cout << "Error: Invalid choice. Please enter again: ";
                cin >> choice;
            }
            else
            {
                break;
            }
        }
        cout << endl;

        switch (choice)
        {
        case 1:
            system("cls");
            addBook(library);
            system("cls");
            cout << ">>>Book Added to Library" << endl;
            break;

        case 2:
            system("cls");
            removeBook(library);
            break;
        case 3:
            system("cls");
            searchBook(library);
            break;
        case 4:
            system("cls");
            cout << ">>>Available books in the library are following :" << endl;
            library.displayAvailableBooks();
            break;
        case 5:
            system("cls");
            checkoutBook(library);
            break;
        case 6:
            system("cls");
            cout << "\n>>>Loading Member Management Menu...Please Wait...\n";
            cout << endl;
            Sleep(2000);
            system("cls");
            manageMembers(members, numMembers);
            break;
        case 7:
            system("cls");
            cout << "\n>>>Exiting the program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 7." << endl;
            break;
        }
        cout << endl;
    }
    return 0;
}
