#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100 + 5;
const int INF = 1000000000;
int cnt, d[maxn][maxn], id[maxn];

int ID(int x) {
    if (id[x] >= 0) return id[x];
    else return id[x] = cnt++;
}

int main() {
    int kase = 0;
    int u, v;
    while (scanf("%d%d", &u, &v) == 2 && u) {
        cnt = 0;
        memset(id, -1, sizeof(id));
        for (int i = 0; i < maxn; ++i) {
            d[i][i] = 0;
            for (int j = 0; j < maxn; ++j)
                d[i][j] = d[j][i] = INF;
        }
        d[ID(u)][ID(v)] = 1;
        while (scanf("%d%d", &u, &v) == 2 && u) {
            d[ID(u)][ID(v)] = 1;
        }
        for (int k = 0; k < cnt; ++k)
            for (int i = 0; i < cnt; ++i)
                for (int j = 0; j < cnt; ++j)
                    if (d[i][k] < INF && d[k][j] < INF)
                        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        int sum = 0, p = 0;
        for (int i = 0; i < cnt; ++i)
            for (int j = 0; j < cnt; ++j)
                if (i != j && d[i][j] < INF) {
                    sum += d[i][j]; ++p;
                }
        printf("Case %d: average length between pages = %.3f clicks\n", ++kase, ((double)sum) / p);
    }
    return 0;
}