#include <iostream>
#include <string>
#include <iomanip> 
using namespace std;

struct Book {
    int id;
    string title;
    string author;
};

Book* books = NULL;
int capacity = 10;
int size = 0;


const int MAX_UNDO = 100;
int undoStack[MAX_UNDO];
int top = -1;


void pushUndo(int bookID) {
    if (top < MAX_UNDO - 1) {
        undoStack[++top] = bookID;
    } else {
        cout << "Undo stack is full!\n";
    }
}


int popUndo() {
    if (top >= 0) {
        return undoStack[top--];
    } else {
        cout << "Nothing to undo!\n";
        return -1;
    }
}


void resizeArray() {
    if (size >= capacity) {
        capacity *= 2;
        Book* newBooks = new Book[capacity];
        for (int i = 0; i < size; i++) {
            newBooks[i] = books[i];
        }
        delete[] books;
        books = newBooks;
    }
}


void addBook() {
    resizeArray();
    Book newBook;
    cout << "Enter Book ID: ";
    cin >> newBook.id;
    cin.ignore(); 
    cout << "Enter Title: ";
    getline(cin, newBook.title);
    cout << "Enter Author: ";
    getline(cin, newBook.author);

    books[size++] = newBook;

    cout << "Book added successfully!\n";
}


void deleteBook() {
    int deleteID;
    cout << "Enter Book ID to delete: ";
    cin >> deleteID;

    bool found = false;
    for (int i = 0; i < size; i++) {
        if (books[i].id == deleteID) {
            pushUndo(books[i].id); 
            for (int j = i; j < size - 1; j++) {
                books[j] = books[j + 1];
            }
            size--;
            found = true;
            cout << "Book deleted.\n";
            break;
        }
    }

    if (!found) {
        cout << "Book ID not found.\n";
    }
}


void undoDelete() {
    int lastDeletedID = popUndo();
    if (lastDeletedID == -1) return;

    resizeArray();
    Book* ptr = &books[size];
    ptr->id = lastDeletedID;
    cin.ignore();
    cout << "Enter Title of restored book: ";
    getline(cin, ptr->title);
    cout << "Enter Author of restored book: ";
    getline(cin, ptr->author);
    size++;
    cout << "Undo successful. Book restored.\n";
}


void searchBook() {
    int searchID;
    cout << "Enter Book ID to search: ";
    cin >> searchID;

    bool found = false;
    for (int i = 0; i < size; i++) {
        if (books[i].id == searchID) {
            cout << "Book Found:\n";
            cout << "ID: " << books[i].id << "\n";
            cout << "Title: " << books[i].title << "\n";
            cout << "Author: " << books[i].author << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Book ID not found.\n";
    }
}


void displayBooks() {
    if (size == 0) {
        cout << "No books in library.\n";
        return;
    }

    cout << left << setw(10) << "ID" << setw(30) << "Title" << setw(30) << "Author" << "\n";
    cout << "--------------------------------------------------------------\n";
    for (int i = 0; i < size; i++) {
        cout << left << setw(10) << books[i].id
             << setw(30) << books[i].title
             << setw(30) << books[i].author << "\n";
    }
}


void menu() {
    int choice;
    do {
        cout << "\n=== Mini Library Management ===\n";
        cout << "1. Add Book\n";
        cout << "2. Delete Book\n";
        cout << "3. Undo Delete\n";
        cout << "4. Search Book\n";
        cout << "5. Display All Books\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addBook(); break;
            case 2: deleteBook(); break;
            case 3: undoDelete(); break;
            case 4: searchBook(); break;
            case 5: displayBooks(); break;
            case 6: cout << "Exiting program. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 6);
}

int main() {
    books = new Book[capacity]; 
    menu();
    delete[] books; 
    return 0;
}