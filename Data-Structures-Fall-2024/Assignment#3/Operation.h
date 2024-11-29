
// Main functions for CRUD operations
void create_Book_Record(AVL_Node *&root, BookRecord *&head, BookRecord *&tail)
{
    string ISSN, title;
    int reference_copies, issue_copies;
    vector<string> authors;
    string author;

    cout << "Enter ISSN: ";
    cin >> ISSN;
    cin.ignore();
    cout << "Enter Title: ";
    getline(cin, title);
    cout << "Enter Number of Authors: ";
    int num_authors;
    cin >> num_authors;
    cin.ignore();
    for (int i = 0; i < num_authors; ++i)
    {
        cout << "Enter Author Name: ";
        getline(cin, author);
        authors.push_back(author);
    }
    cout << "Enter Number of Reference Copies: ";
    cin >> reference_copies;
    while (reference_copies < 0 || reference_copies >= 100)
    {
        cout << "Invalid input. Number of reference copies should be between 0 and 99. Please enter again: ";
        cin >> reference_copies;
    }
    cout << "Enter Number of Issuable Copies: ";
    cin >> issue_copies;
    while (issue_copies < 0 || issue_copies >= 100)
    {
        cout << "Invalid input. Number of issue copies should be between 0 and 99. Please enter again: ";
        cin >> issue_copies;
    }

    BookRecord *new_Rec = new BookRecord(ISSN, title, authors, reference_copies, issue_copies);
    root = insert_AVL(root, ISSN, new_Rec);
    insert_Double_LL(head, tail, new_Rec);
}

void review_Book_Record(AVL_Node *root, string ISSN)
{
    if (!root)
    {
        cout << "Book not found!" << endl;
        return;
    }

    if (ISSN < root->ISSN)
        review_Book_Record(root->left, ISSN);
    else if (ISSN > root->ISSN)
        review_Book_Record(root->right, ISSN);

    else
    {
        BookRecord *record = root->bookRecord;
        cout << "ISSN: " << record->ISSN << endl;
        cout << "Title: " << record->title << endl;
        cout << "Authors: ";
        for (const auto &author : record->authors)
            cout << author << " ";
        cout << endl;
        cout << "Reference Copies: " << record->reference_copies << endl;
        cout << "Issuable Copies: " << record->issuable_copies << endl;
    }
}

void update_Book_Record(AVL_Node *root, string ISSN)
{
    if (!root)
    {
        cout << "Book not found!" << endl;
        return;
    }
    if (ISSN < root->ISSN)
        update_Book_Record(root->left, ISSN);
    else if (ISSN > root->ISSN)
        update_Book_Record(root->right, ISSN);
    else
    {
        BookRecord *record = root->bookRecord;
        cout << "Update Title (leave blank to keep current): ";
        string new_Title;
        cin.ignore();
        getline(cin, new_Title);
        if (!new_Title.empty())
            record->title = new_Title;

        cout << "Update Number of Reference Copies (-1 to keep current): ";
        int new_ref_copies;
        cin >> new_ref_copies;
        if (new_ref_copies != -1)
            record->reference_copies = new_ref_copies;

        cout << "Update Number of Issuable Copies (-1 to keep current): ";
        int new_issue_copies;
        cin >> new_issue_copies;
        if (new_issue_copies != -1)
            record->issuable_copies = new_issue_copies;
    }
}

void delete_Book_Record(AVL_Node *&root, BookRecord *&head, BookRecord *&tail, string ISSN)
{
    root = delete_AVL(root, ISSN);
    delete_Double_LL(head, tail, ISSN);
}

void Menu()
{
    cout << "\nLibrary Database System\n";
    cout << "1. Create Book Record\n";
    cout << "2. Review Book Record\n";
    cout << "3. Update Book Record\n";
    cout << "4. Delete Book Record\n";
    cout << "5. Exit\n";
    cout << "Enter your option: ";
}

void Selection(AVL_Node *&root, BookRecord *&head, BookRecord *&tail)
{
    while (true)
    {
        Menu();
        int option;
        cin >> option;

        while (option > 5 || option < 0)
        {
            cout << "Invalid option. Please enter a valid option (1-5): ";
            cin >> option;
        }

        if (option == 1)
        {
            create_Book_Record(root, head, tail);
        }
        if (option == 2)
        {
            string ISSN;
            cout << "Enter ISSN to Review: ";
            cin >> ISSN;
            review_Book_Record(root, ISSN);
        }
        if (option == 3)
        {
            string ISSN;
            cout << "Enter ISSN to Update: ";
            cin >> ISSN;
            update_Book_Record(root, ISSN);
        }
        if (option == 4)
        {
            string ISSN;
            cout << "Enter ISSN to Delete: ";
            cin >> ISSN;
            delete_Book_Record(root, head, tail, ISSN);
        }
        if (option == 5)
        {
            cout << "Exiting..." << endl;
            break;
        }
    }
}