#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 25;

int n, k, num;
vector<int> road[maxn];
int linked[maxn], vis[maxn];
int route[maxn];

void init() {
    memset(linked, 0, sizeof(linked));
    for (int i = 1; i <= n; ++i) if (i != k) {
        sort(road[i].begin(), road[i].end());
        memset(vis, 0, sizeof(vis));
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            vis[u] = 1;
            if (u == k) {
                linked[i] = 1; break;
            }
            for (auto it = road[u].begin(); it != road[u].end(); ++it) {
                if (!vis[*it]) q.push(*it);
            }
        }
    }
    linked[k] = 1;
}

bool notvis(int v, int d) {
    for (int i = 0; i < d; ++i)
        if (route[i] == v) return false;
    return true;
}

void dfs(int d) {
    if (route[d] == k) {
        for (int i = 0; i < d; ++i) printf("%d ", route[i]);
        printf("%d\n", route[d]);
        ++num;
    }
    int u = route[d];
    for (auto it = road[u].begin(); it != road[u].end(); ++it) if (notvis(*it, d) && linked[*it]) {
        route[d + 1] = *it;
        dfs(d + 1);
    }
}

int main() {
    int a, b, T = 0;
    while (scanf("%d", &k) == 1) {
        for (int i = 0; i < maxn; ++i) road[i].clear();
        n = 0;
        while (scanf("%d%d", &a, &b) == 2 && a && b) {
            if (n < a) n = a;
            if (n < b) n = b;
            road[a].push_back(b); road[b].push_back(a);
        }
        init();
        num = 0;
        route[0] = 1;
        printf("CASE %d:\n", ++T);
        dfs(0);
        printf("There are %d routes from the firestation to streetcorner %d.\n", num, k);
    }
    return 0;
}