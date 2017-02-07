#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int a[] = {-1, -1, -2, -2, 1, 1, 2, 2};
const int b[] = {-2, 2, -1, 1, -2, 2, -1, 1};

int vis[100], d[100];

inline int id(int a, int b) {
    return a * 10 + b;
}

bool isvalid(int a, int b) {
    return a >= 0 && a <= 7 && b >= 0 && b <= 7;
}

int main() {
    char x[3], y[3];
    int x1, x2, y1, y2, xid, yid;
    while (scanf("%s%s", x, y) == 2) {
        memset(vis, 0, sizeof(vis)); memset(d, 0, sizeof(d));
        x1 = x[0] - 'a'; x2 = x[1] - '1'; xid = id(x1, x2);
        y1 = y[0] - 'a'; y2 = y[1] - '1'; yid = id(y1, y2);
        queue<int> q;
        q.push(xid);
        while (q.size()) {
            int u = q.front(); q.pop();
            int a0 = u / 10, b0 = u % 10;
            vis[u] = 1;
            if (u == yid) break;
            for (int i = 0; i < 8; ++i) {
                int a1 = a0 + a[i], b1 = b0 + b[i], id1 = id(a1, b1);
                if (isvalid(a1, b1) && !vis[id1]) {
                    q.push(id1);
                    d[id1] = d[u] + 1;
                }
            }
        }
        printf("To get from %s to %s takes %d knight moves.\n", x, y, d[yid]);
    }
    return 0;
}