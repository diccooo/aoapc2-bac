#include <cstdio>

int main() {
    int T = 0;
    int n, m;
    int x[10];
    char xtmp[10];
    char leaves[200];
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; ++i) {
            scanf("%s", xtmp);
            x[i] = xtmp[1] - '0';
        }
        scanf("%s", leaves);
        printf("S-Tree #%d:\n", ++T);
        scanf("%d", &m);
        while (m--) {
            scanf("%s", &xtmp[1]);
            int index = 0;
            for (int i = 0; i < n; ++i) {
                index = (index << 1) + (xtmp[x[i]] - '0');
            }
            printf("%c", leaves[index]);
        }
        printf("\n\n");
    }
    return 0;
}