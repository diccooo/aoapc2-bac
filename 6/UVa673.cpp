#include <iostream>
#include <string>
#include <sstream>
#include <stack>

using namespace std;

int main() {
    string s;
    getline(cin, s);
    stringstream ss(s);
    int T;
    ss >> T;
    while (T--) {
        bool f = 1;
        stack<char> st;
        getline(cin, s);
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(' || s[i] == '[')
                st.push(s[i]);
            if (s[i] == ')') {
                if (st.size() && st.top() == '(') st.pop();
                else {
                    f = 0; break;
                }
            }
            if (s[i] == ']') {
                if (st.size() && st.top() == '[') st.pop();
                else {
                    f = 0; break;
                }
            }
        }
        if (st.size()) f = 0;
        printf(f ? "Yes\n" : "No\n");
    }
    return 0;
}