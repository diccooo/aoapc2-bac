#include <iostream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

void tokenize(string &s, map<string, string> &dict) {
    for (auto i = s.begin(); i != s.end(); ++i) {
        if (*i == '{' || *i == '}' || *i == ':' || *i == ',')
            *i = ' ';
    }
    stringstream ss(s);
    string key, val;
    while (ss >> key) {
        ss >> val;
        dict[key] = val;
    }
}

void compdict(const map<string, string> &dict1, const map<string, string> &dict2) {
    if (dict1 == dict2)
        cout << "No changes\n";
    else {
        int n = 0;
        for (auto i = dict2.begin(); i != dict2.end(); ++i) {
            if (!dict1.count(i->first)) {
                if (n++) cout << ',';
                else cout << '+';
                cout << i->first;
            }
        }
        if (n) cout << endl;
        n = 0;
        for (auto i = dict1.begin(); i != dict1.end(); ++i) {
            if (!dict2.count(i->first)) {
                if (n++) cout << ',';
                else cout << '-';
                cout << i->first;
            }
        }
        if (n) cout << endl;
        n = 0;
        for (auto i = dict1.begin(); i != dict1.end(); ++i) {
            if (dict2.count(i->first) && dict2.at(i->first) != i->second) {
                if (n++) cout << ',';
                else cout << '*';
                cout << i->first;
            }
        }
        if (n) cout << endl;
    }
    cout << endl;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        string oldstr, newstr;
        cin >> oldstr;
        cin >> newstr;
        map<string, string> olddict, newdict;
        tokenize(oldstr, olddict);
        tokenize(newstr, newdict);
        compdict(olddict, newdict);
    }
    return 0;
}