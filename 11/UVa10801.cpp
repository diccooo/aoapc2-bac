#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <algorithm>

using namespace std;

const int fl = 100;
const int INF = 1000000000;
int v[fl], d[fl], w[fl][fl], t[5];

int main() {
    string s;
    while (getline(cin, s)) {
        stringstream s1(s);
        int n, k;
        s1 >> n >> k;
        getline(cin, s); stringstream s2(s);
        for (int i = 0; i < n; ++i) s2 >> t[i];
        memset(v, 0, sizeof(v));
        for (int i = 0; i < fl; ++i) {
            d[i] = INF;
            for (int j = 0; j < fl; ++j)
                w[i][j] = INF;
        }
        d[0] = 0;
        int floor[fl], cnt;
        for (int i = 0; i < n; ++i) {
            getline(cin, s); stringstream s3(s);
            cnt = 0;
            while (s3 >> floor[cnt]) ++cnt;
            for (int j = 0; j < cnt; ++j)
                for (int k = j + 1; k < cnt; ++k) {
                    int a = floor[j], b = floor[k];
                    w[a][b] = w[b][a] = min(w[a][b], t[i] * (b - a));
                }
        }
        for (int i = 0; i < fl; ++i) {
            int x, m = INF;
            for (int y = 0; y < fl; ++y)
                if (!v[y] && d[y] <= m) {
                    x = y;
                    m = d[y];
                }
            v[x] = 1;
            for (int y = 0; y < fl; ++y) if (w[x][y] < INF)
                d[y] = min(d[y], d[x] + w[x][y] + 60);
        }
        if (d[k] == 0) printf("0\n");
        else if (d[k] < INF) printf("%d\n", d[k] - 60);
        else printf("IMPOSSIBLE\n");
    }
    return 0;
}