// Lab 6 - 2

#include <iostream>
#include <cstring>

using namespace std;

class Book {
private:
    char *naslovNaKnigata;
    int *isbnNaKnigata;
    int brNaStraniNaKnigata;

    void copy(const Book &b) {
        this->naslovNaKnigata = new char[strlen(b.naslovNaKnigata) + 1];
        strcpy(this->naslovNaKnigata, b.naslovNaKnigata);
        this->isbnNaKnigata = new int[5];
        memcpy(this->isbnNaKnigata, b.isbnNaKnigata, 5 * sizeof(int));
        this->brNaStraniNaKnigata = b.brNaStraniNaKnigata;
    }

    void freeMemory() {
        delete[] naslovNaKnigata;
        delete[] isbnNaKnigata;
    }

public:
    Book() {
        this->naslovNaKnigata = new char[1];
        this->naslovNaKnigata[0] = '\0';
        this->isbnNaKnigata = nullptr;
        this->brNaStraniNaKnigata = 0;
    }

    Book(char *name, int *isbn, int pages) {
        this->naslovNaKnigata = new char[strlen(name) + 1];
        strcpy(this->naslovNaKnigata, name);
        this->isbnNaKnigata = new int[5];
        memcpy(this->isbnNaKnigata, isbn, 5 * sizeof(int));
        this->brNaStraniNaKnigata = pages;
    }

    Book(const Book &b) {
        copy(b);
    }

    Book &operator=(const Book &b) {
        if (this != &b) {
            freeMemory();
            copy(b);
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Book &b) {
        out << "Title: " << b.naslovNaKnigata << " ISBN: [ ";
        for (int i = 0; i < 5; ++i) {
            if (i <= 3) {
                out << b.isbnNaKnigata[i] << " ";
            } else {
                out << b.isbnNaKnigata[i];
            }
        }
        out << " ]" << endl;
        return out;
    }

    int getPages() const {
        return brNaStraniNaKnigata;
    }

    int *getIsbn() const {
        return isbnNaKnigata;
    }

    bool operator==(const Book &b) const {
        for (int i = 0; i < 5; ++i) {
            if (this->isbnNaKnigata[i] != b.isbnNaKnigata[i]) {
                return false;
            }
        }
        return true;
    }

    ~Book() {
        freeMemory();
    }
};

class BorrowABook {
private:
    char imeNaBibliotekata[100];
    Book *knigi;
    int brNaKnigi;

    void copy(const BorrowABook &bb) {
        strcpy(this->imeNaBibliotekata, bb.imeNaBibliotekata);
        this->brNaKnigi = bb.brNaKnigi;
        this->knigi = new Book[bb.brNaKnigi];
        for (int i = 0; i < brNaKnigi; ++i) {
            this->knigi[i] = bb.knigi[i];
        }
    }

public:
    BorrowABook() {
        strcpy(this->imeNaBibliotekata, "");
        this->brNaKnigi = 0;
        this->knigi = new Book[0];
    }

    BorrowABook(char *name) {
        strcpy(this->imeNaBibliotekata, name);
        this->brNaKnigi = 0;
        this->knigi = new Book[0];
    }

    BorrowABook(const BorrowABook &bb) {
        copy(bb);
    }

    BorrowABook &operator=(const BorrowABook &bb) {
        if (this != &bb) {
            delete[] knigi;
            copy(bb);
        }
        return *this;
    }

    bool operator==(const BorrowABook &bb) const {
        for (int i = 0; i < brNaKnigi; ++i) {
            if (knigi[i] == bb.knigi[i]) {
                return true;
            }
        }
        return false;
    }

    BorrowABook &operator+=(const Book &nova) {
        Book *tmp = new Book[brNaKnigi + 1];
        for (int i = 0; i < brNaKnigi; ++i) {
            tmp[i] = knigi[i];
        }
        tmp[brNaKnigi++] = nova;
        delete[] knigi;
        knigi = tmp;
        return *this;
    }

    BorrowABook &operator-=(const Book &nova) {
        for (int i = 0; i < brNaKnigi; ++i) {
            if (knigi[i] == nova) {
                Book *tmp = new Book[brNaKnigi - 1];
                for (int j = 0; j < i; ++j) {
                    tmp[j] = knigi[j];
                }
                for (int j = i + 1; j < brNaKnigi; ++j) {
                    tmp[j - 1] = knigi[j];
                }
                delete[] knigi;
                knigi = tmp;
                --brNaKnigi;
                break;
            }
        }
        return *this;
    }

    void printNumberOfPages(int max) {
        cout << imeNaBibliotekata << endl;
        for (int i = 0; i < brNaKnigi; ++i) {
            if (knigi[i].getPages() > max) {
                cout << knigi[i] << endl;
            }
        }
    }

    ~BorrowABook() {
        delete[] knigi;
    }

};

int main() {
    BorrowABook library("FINKI-Library");
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        char title[100];
        int isbn[5];
        int pages;

        cin >> title;

        for (int j = 0; j < 5; j++)
            cin >> isbn[j];

        cin >> pages;

        Book nov = Book(title, isbn, pages);

        //adding a new book
        library += nov;

    }
    //the book which has the same isbn as some previous one
    char title[100];
    int isbn[5];
    int pages;
    cin >> title;
    for (int i = 0; i < 5; i++)
        cin >> isbn[i];
    cin >> pages;

    Book greshka = Book(title, isbn, pages);

    //deleting a book
    library -= greshka;

    library.printNumberOfPages(150);

    return 0;
}