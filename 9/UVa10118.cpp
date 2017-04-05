#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 40 + 5;
int n, piles[4][maxn], dd[maxn][maxn][maxn][maxn], top[4];
bool hash[25];

int dfs(int count) {
    if (dd[top[0]][top[1]][top[2]][top[3]] != -1)
        return dd[top[0]][top[1]][top[2]][top[3]];
    int &ans = dd[top[0]][top[1]][top[2]][top[3]];
    ans = 0;
    if (count == 5)
        return ans;
    for (int i = 0; i < 4; ++i) {
        if (top[i] == n) continue;
        int color = piles[i][top[i]];
        ++top[i];
        if (hash[color]) {
            hash[color] = false;
            ans = max(ans, dfs(count - 1) + 1);
            hash[color] = true;
        }
        else {
            hash[color] = true;
            ans = max(ans, dfs(count + 1));
            hash[color] = false;
        }
        --top[i];
    }
    return ans;
}

int main() {
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < 4; ++j)
                scanf("%d", &piles[j][i]);
        memset(hash, 0, sizeof(hash));
        memset(dd, -1, sizeof(dd));
        for (int i = 0; i < 4; ++i) top[i] = 0;
        printf("%d\n", dfs(0));
    }
    return 0;
}