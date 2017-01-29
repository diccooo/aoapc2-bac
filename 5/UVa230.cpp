#include <iostream>
#include <string>
#include <list>
#include <map>

using namespace std;

struct Book {
    string title, author;
    bool operator < (const Book &b) const {
        return author < b.author || (author == b.author && title < b.title);
    }
};

int main() {
    list<Book> shelves, borrowed;
    map<string, Book> books;
    string s;
    while (getline(cin, s) && s != "END") {
        Book b;
        auto pos = s.find_last_of('"');
        b.title = s.substr(1, pos - 1), b.author = s.substr(pos + 5);
        shelves.push_back(b);
        books[b.title] = b;
    }
    shelves.sort();
    while (getline(cin, s) && s != "END") {
        if (s[0] == 'B') {
            string title = s.substr(8, s.size() - 9);
            for (auto i = shelves.begin(); i != shelves.end(); ++i) {
                if (i->title == title) {
                    shelves.erase(i);
                    break;
                }
            }
        }
        if (s[0] == 'R') {
            string title = s.substr(8, s.size() - 9);
            borrowed.push_back(books[title]);
        }
        if (s[0] == 'S') {
            borrowed.sort();
            while (borrowed.size()) {
                Book b = borrowed.front();
                borrowed.pop_front();
                shelves.push_back(b);
                shelves.sort();
                cout << "Put \"" << b.title << "\" ";
                for (auto i = shelves.begin(); i != shelves.end(); ++i) {
                    if (i->title == b.title) {
                        if (i == shelves.begin())
                            cout << "first\n";
                        else {
                            auto a = i; a--;
                            cout << "after \"" << a->title << "\"\n";
                        }
                        break;
                    }
                }
            }
            cout << "END" << endl;
        }
    }
    return 0;
}