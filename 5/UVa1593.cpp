#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const int maxn = 100;
const int maxl = 1005;

string words[maxl][maxn];

int main() {
    int n = 0, mm = 0;
    string l;
    while (getline(cin, l)) {
        stringstream ss(l);
        int m = 0;
        while (ss >> words[n][m]) {
            ++m;
        }
        if (mm < m)
            mm = m;
        ++n;
    }
    string line[maxl];
    for (int i = 0; i < mm; ++i) {
        int mw = 0;
        for (int j = 0; j < n; ++j) {
            if (mw < words[j][i].size())
                mw = words[j][i].size();
        }
        for (int j = 0; j < n; ++j) {
            if (words[j][i] == "") continue;
            line[j] += words[j][i] + string(mw - words[j][i].size() + 1, ' ');
        }
    }
    for (int i = 0; i < n; ++i) {
        line[i].erase(line[i].find_last_not_of(' ') + 1);
        cout << line[i] << endl;
    }
    return 0;
}