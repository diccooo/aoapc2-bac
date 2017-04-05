#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 100000 + 5;
int n, l, item[maxn];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &l);
        for (int i = 0; i < n; ++i) scanf("%d", &item[i]);
        sort(item, item + n);
        int ans = 0;
        int L = 0, R = n - 1;
        for (;;) {
            if (L > R) break;
            if (L == R) {
                ++ans; break;
            }
            if (item[L] + item[R] <= l) {
                ++ans; ++L; --R;
            }
            else {
                ++ans; --R;
            }
        }
        printf("%d\n", ans);
        if (T) printf("\n");
    }
    return 0;
}