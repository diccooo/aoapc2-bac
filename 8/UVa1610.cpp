#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int maxn = 1000 + 5;
string names[maxn];
int n;

int main() {
    while (cin >> n && n) {
        for (int i = 0; i < n; ++i) cin >> names[i];
        sort(names, names + n);
        string &s1 = names[n / 2 - 1], &s2 = names[n / 2];
        string s;
        int k = 0;
        while (k < s1.size() && k < s2.size() && s1[k] == s2[k]) ++k;
        if (k == s1.size() || k == s1.size() - 1) s = s1;
        else if (k < s1.size() - 1 && k < s2.size() - 1) {
            s = s1.substr(0, k);
            s += s1[k] + 1;
        }
        else if (k == s2.size() - 1 && s1[k] + 1 != s2[k]) {
            s = s1.substr(0, k);
            s += s1[k] + 1;
        }
        else if (k == s2.size() - 1) {
            ++k;
            s = s1.substr(0, k);
            while (k < s1.size() - 1) {
                if (s1[k] != 'Z') {
                    s += s1[k] + 1; break;
                }
                else
                    s += 'Z'; ++k;
            }
            if (k == s1.size() - 1) {
                s += s1[k];
            }
        }
        cout << s << "\n";
    }
    return 0;
}