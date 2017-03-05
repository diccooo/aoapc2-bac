#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int maxn = 1000 + 5;

int pos[maxn];
vector<int> tree[maxn];

int main() {
    int n, tmp;
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &tmp);
            pos[tmp] = i;
            tree[i].clear();
        }
        stack<int> s;
        int root;
        scanf("%d", &root);
        s.push(root);
        for (int i = 1; i < n; ++i) {
            scanf("%d", &tmp);
            for (;;) {
                int u = s.top();
                if (u == root || pos[u] + 1 < pos[tmp]) {
                    tree[u].push_back(tmp);
                    s.push(tmp);
                    break;
                }
                else
                    s.pop();
            }
        }
        for (int i = 1; i <= n; ++i) {
            printf("%d:", i);
            sort(tree[i].begin(), tree[i].end());
            for (auto it = tree[i].begin(); it != tree[i].end(); ++it)
                printf(" %d", *it);
            printf("\n");
        }
    }
    return 0;
}