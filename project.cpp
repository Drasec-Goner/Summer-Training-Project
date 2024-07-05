#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool isIssued;
    string issuedTo;

    Book(int id, string title, string author)
        : id(id), title(title), author(author), isIssued(false) {}
};

class Library {
private:
    vector<Book> books;
    int generateBookId() {
        return books.size() + 1;
    }

public:
    void addBook(string title, string author) {
        int id = generateBookId();
        books.push_back(Book(id, title, author));
        cout << "Book added with ID: " << id << endl;
    }

    void searchBookByTitle(string title) {
        for (const auto& book : books) {
            if (book.title == title) {
                cout << "Book found: ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author << ", Status: " << (book.isIssued ? "Issued" : "Available") << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void searchBookById(int id) {
        for (const auto& book : books) {
            if (book.id == id) {
                cout << "Book found: ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author << ", Status: " << (book.isIssued ? "Issued" : "Available") << endl;
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void issueBook(int id, string studentName) {
        for (auto& book : books) {
            if (book.id == id) {
                if (!book.isIssued) {
                    book.isIssued = true;
                    book.issuedTo = studentName;
                    cout << "Book issued to " << studentName << endl;
                } else {
                    cout << "Book already issued." << endl;
                }
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void returnBook(int id) {
        for (auto& book : books) {
            if (book.id == id) {
                if (book.isIssued) {
                    book.isIssued = false;
                    book.issuedTo = "";
                    cout << "Book returned." << endl;
                } else {
                    cout << "Book was not issued." << endl;
                }
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void listAllBooks() {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.id < b.id;
        });
        for (const auto& book : books) {
            cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author << ", Status: " << (book.isIssued ? "Issued" : "Available") << endl;
        }
    }

    void deleteBook(int id) {
        auto it = remove_if(books.begin(), books.end(), [id](const Book& book) {
            return book.id == id;
        });
        if (it != books.end()) {
            books.erase(it, books.end());
            cout << "Book deleted." << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }
};

int main() {
    Library library;
    int choice;
    string title, author, studentName;
    int id;

    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add New Book\n";
        cout << "2. Search Book by Title\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. List All Books\n";
        cout << "7. Delete Book\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            library.addBook(title, author);
            break;
        case 2:
            cout << "Enter title: ";
            cin.ignore();
            getline(cin, title);
            library.searchBookByTitle(title);
            break;
        case 3:
            cout << "Enter ID: ";
            cin >> id;
            library.searchBookById(id);
            break;
        case 4:
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, studentName);
            library.issueBook(id, studentName);
            break;
        case 5:
            cout << "Enter ID: ";
            cin >> id;
            library.returnBook(id);
            break;
        case 6:
            library.listAllBooks();
            break;
        case 7:
            cout << "Enter ID: ";
            cin >> id;
            library.deleteBook(id);
            break;
        case 8:
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
