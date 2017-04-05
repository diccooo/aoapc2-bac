#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100 + 5;
int r, c, h[maxn][maxn], d[maxn][maxn];

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int dp(int i, int j) {
    int &ans = d[i][j];
    if (ans > 0) return ans;
    ans = 0;
    for (int k = 0; k < 4; ++k) {
        int x = i + dx[k], y = j + dy[k];
        if (x >= 0 && x < r && y >= 0 && y < c && h[x][y] < h[i][j]) {
            ans = max(ans, dp(x, y));
        }
    }
    ++ans;
    return ans;
}

int main() {
    int T;
    char name[200];
    scanf("%d", &T);
    while (T--) {
        scanf("%s%d%d", name, &r, &c);
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                scanf("%d", &h[i][j]);
        memset(d, 0, sizeof(d));
        int ans = 0;
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                ans = max(ans, dp(i, j));
        printf("%s: %d\n", name, ans);
    }
    return 0;
}