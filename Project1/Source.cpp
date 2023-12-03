#include <iostream>
#include <string>
using namespace std;
const int MAX_BOOKS = 500;
const int MAX_USERS = 50;
const int MAX_BORROWINGS = 200;

class Book {
public:
    string title;
    string author;
    int rating;
    bool available;
    string borrowedDate;
    string returnedDate;
    Book() {

    }

    Book(const string& t, const string& a, int r): title(t), author(a), rating(r), available(true) {}

    void borrowBook() {
        if (available) {
            available = false;
            borrowedDate = getCurrentDate();
            returnedDate = "";
            std::cout << "Book borrowed: " << title << " by " << author << std::endl;
        }
        else {
            std::cout << "Book is not available for borrowing." << std::endl;
        }
    }

    void returnBook() {
        if (!available) {
            available = true;
            returnedDate = getCurrentDate();
            std::cout << "Book returned: " << title << " by " << author << std::endl;
        }
        else {
            std::cout << "Book is already available." << std::endl;
        }
    }

    std::string getCurrentDate() const {
        // Simulated function to get the current date
        return "01/01/2023";
    }
};

class User {
public:
    std::string name;
    std::string phoneNumber;
    std::string address;
    User() {

    }
    User(const string& n, const string& phone, const string& addr)
        : name(n), phoneNumber(phone), address(addr) {
        name = n;
        phoneNumber = phone;
        address = addr;
    
    }
};

class Library {
private:
    Book books[MAX_BOOKS];
    int numBooks;
    User users[MAX_USERS];
    int numUsers;
    Book borrowings[MAX_BORROWINGS];
    int numBorrowings;
    User* currentUser;

public:

    Library() : numBooks(0), numUsers(0), numBorrowings(0), currentUser(nullptr) {}
    // User management
    void addUser(const string& name, const string& phoneNumber, const string& address) {
        if (numUsers < MAX_USERS) {
            users[numUsers++] = User(name, phoneNumber, address);
            cout << "User added: " << name << endl;
        }
        else {
           cout << "Maximum number of users reached." << endl;
        }
    }

    void loginUser(const std::string& name) {
        for (int i = 0; i < numUsers; ++i) {
            if (users[i].name == name) {
                currentUser = &users[i];
                std::cout << "User logged in: " << name << std::endl;
                return;
            }
        }
        std::cout << "User not found." << std::endl;
    }

    // Book management
    void addBook(const string& title, const string& author, int rating) {
        if (numBooks < MAX_BOOKS) {
            books[numBooks++] = Book(title, author, rating);
            cout << "Book added: " << title << " by " << author << endl;
        }
        else {
            cout << "Maximum number of books reached." << endl;
        }
    }

    // User actions
    void borrowBook(const string& title, const string& author) {
        if (currentUser) {
            for (int i = 0; i < numBooks; ++i) {
                if (books[i].title == title && books[i].author == author) {
                    books[i].borrowBook();
                    if (numBorrowings < MAX_BORROWINGS) {
                        borrowings[numBorrowings++] = books[i];
                    }
                    else {
                        cout << "Maximum number of borrowings reached." << endl;
                    }
                    return;
                }
            }
            cout << "Book not found." << endl;
        }
        else {
            cout << "Please log in first." << endl;
        }
    }

    void returnBook(const string& title, const string& author) {
        if (currentUser) {
            for (int i = 0; i < numBorrowings; ++i) {
                if (borrowings[i].title == title && borrowings[i].author == author) {
                    borrowings[i].returnBook();
                    return;
                }
            }
            cout << "Book not found in borrowings." << endl;
        }
        else {
            cout << "Please log in first." << endl;
        }
    }

    void searchBooks(const string& query) {
        cout << "Search results:" << endl;
        for (int i = 0; i < numBooks; ++i) {
            if (books[i].title.find(query) != string::npos || books[i].author.find(query) != string::npos) {
                cout << "  " << books[i].title << " by " << books[i].author << " (Rating: " << books[i].rating << ")" << endl;
            }
        }
    }

    void viewLibrary() {
        cout << "Library contents:" << endl;
        for (int i = 0; i < numBooks; ++i) {
            cout << books[i].title << " by " << books[i].author
                << " (Rating: " << books[i].rating << ") - "
                << (books[i].available ? "Available" : "Borrowed") << endl;
        }
    }

    // Administrator actions
    void addDeleteUser(bool add, const std::string& name) {
        if (currentUser && currentUser->name == "admin") {
            if (add) {
                addUser(name, "", "");
            }
            else {
                for (int i = 0; i < numUsers; ++i) {
                    if (users[i].name == name) {
                        for (int j = i; j < numUsers - 1; ++j) {
                            users[j] = users[j + 1];
                        }
                        --numUsers;
                        std::cout << "User deleted: " << name << std::endl;
                        return;
                    }
                }
                std::cout << "User not found." << std::endl;
            }
        }
        else {
            std::cout << "Only administrators can add/delete users." << std::endl;
        }
    }

    void addBookAdmin(const std::string& title, const std::string& author, int rating) {
        if (currentUser && currentUser->name == "admin") {
            addBook(title, author, rating);
        }
        else {
            std::cout << "Only administrators can add books." << std::endl;
        }
    }

    // Error handling and exceptions
    void handleErrors(const std::string& action) {
        std::cout << "Error: Unable to perform " << action << "." << std::endl;
    }

    // Safety and protection
    bool checkPermission() {
        return currentUser != nullptr;
    }

    // Reports and statistics
    void generateReports() {
        int numAvailableBooks = 0;
        int numBorrowedBooks = 0;

        for (int i = 0; i < numBooks; ++i) {
            if (books[i].available) {
                numAvailableBooks++;
            }
            else {
                numBorrowedBooks++;
            }
        }

        std::cout << "Reports and Statistics:" << std::endl;
        std::cout << "Total Books: " << numBooks << std::endl;
        std::cout << "Available Books: " << numAvailableBooks << std::endl;
        std::cout << "Borrowed Books: " << numBorrowedBooks << std::endl;
    }

    // Instructions and documentation
    void provideInstructions() {
        std::cout << "Library System Instructions:" << std::endl;
        // Add relevant instructions here
    }
};

int main() {
    string user;
    string address;
    string phonenumber;
    Library library;
    cout << "Enter the username , phone number  and address :";
    cin >> user >> address >> phonenumber;
    // Adding users
    library.addUser(user, phonenumber, address);
    cout << "Enter the username , phone number  and address :";
    cin >> user >> address >> phonenumber;
    library.addUser(user, phonenumber, address);
    cout << "Enter the username , phone number  and address :";
    cin >> user >> address >> phonenumber;
    library.addUser(user, phonenumber, address);
    cout << "Enter the username , phone number  and address :";
    cin >> user >> address >> phonenumber;
    library.addUser(user, phonenumber, address);
    cout << "Enter the username , phone number  and address :";
    cin >> user >> address >> phonenumber;
    library.addUser(user, phonenumber, address);
    // Adding books
    int rating;string Books;string Author;
    cout << "Enter the name of book , name of Author and rating";
    getline(cin, Books); cin >> Author >> rating;
    library.addBook(Books, Author, rating);
    cout << "Enter the name of book , name of Author and rating";
    getline(cin, Books); cin >> Author >> rating;
    library.addBook(Books, Author, rating);
    cout << "Enter the name of book , name of Author and rating";
    getline(cin, Books); cin >> Author >> rating;
    library.addBook(Books, Author, rating);
    // Add more books as needed
    cout << "The log in   :";

    // Simulating user login
    library.loginUser(user);

    // User actions
    library.borrowBook(Books, Author);
    library.returnBook(Books, Author);
    library.searchBooks(Books);
    library.viewLibrary();
    cout << "Enter the user admin";
    string admain;
    cin >> admain;
    // Simulating administrator login
    library.loginUser(admain);

    // Administrator actions
    library.addDeleteUser(true, user);
    library.addBookAdmin(Books, Author, rating);
    library.viewLibrary();
    library.generateReports();

    // Logout
    library.loginUser(""); // Logging out by providing an empty username

    return 0;
}
