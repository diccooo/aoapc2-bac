#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 1000 + 5;

int vn, en, time;
vector<int> road[maxn];
int vis[maxn];

int cnt;                        //num of odd points
void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    cnt += road[u].size() % 2;
    for (auto it = road[u].begin(); it != road[u].end(); ++it)
        dfs(*it);
}

int main() {
    int a, b, T = 0;
    while (scanf("%d%d%d", &vn, &en, &time) == 3 && (vn || en || time)) {
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < maxn; ++i)
            road[i].clear();
        for (int i = 0; i < en; ++i) {
            scanf("%d%d", &a, &b);
            road[a].push_back(b);
            road[b].push_back(a);
        }
        int n = 0;
        for (int i = 1; i <= vn; ++i) {
            if (!vis[i] && road[i].size()) {
                cnt = 0;
                dfs(i);
                ++n;                        // 连通分量数+1
                if (cnt > 2) n += (cnt - 2) / 2;         // 奇点个数大于2，连接多余奇点
            }
        }
        n = max(n - 1, 0) + en;         //各个子图的连接数等于分量数-1， max防止en=0时n<0
        printf("Case %d: %d\n", ++T, n * time);
    }
    return 0;
}