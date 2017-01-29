#include <cstdio>
#include <string>

using namespace std;

const int maxn = 120000 + 10;
string words[maxn];

int main() {
    int n = 0;
    char word[100];
    while (scanf("%s", word) == 1) {
        words[n].assign(word);
        ++n;
    }
    const string::size_type sz = 0;
    for (int i = 0; i < n; ++i) {
        bool f = 0;
        for (int j  = 0; j < i; ++j) {
            if (words[i].find(words[j]) == sz) {
                string t = words[i].substr(words[j].size());
                for (int k = 0; k < n; ++k) {
                    if (words[k] == t) {
                        printf("%s\n", words[i].c_str());
                        f = 1;
                        break;
                    }
                }
            }
            if (f) break;
        }
    }
    return 0;
}