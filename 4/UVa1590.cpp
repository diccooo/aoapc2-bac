#include <cstdio>

int ip[1010][4];

int main() {
    int T;
    while (scanf("%d", &T) == 1) {
        for (int i = 0; i < T; ++i) {
            scanf("%d.%d.%d.%d", &ip[i][0], &ip[i][1], &ip[i][2], &ip[i][3]);
        }
        bool f = 0;
        int x = 0, y = 8;
        for (int i = 0; i < 4; ++i) {
            if (f) break;
            for (int j = 7; j >= 0; --j) {
                if (f) break;
                int mask = 255 << j;
                int t = ip[0][i] & mask;
                for (int k = 1; k < T; ++k) {
                    if ((ip[k][i] & mask) != t) {
                        f = 1; break;
                    }
                }
                if (!f) {
                    x = i; y = j;
                }
            }
        }
        if (T == 1) {
            x = 3; y = 0;
        }
        for (int i = 0; i < 4; ++i) {
            if (i)
                printf(".");
            if (i < x)
                printf("%d", ip[0][i]);
            if (i == x)
                printf("%d", ip[0][i] & (255 << y));
            if (i > x)
                printf("0");
        }
        printf("\n");
        for (int i = 0; i < 4; ++i) {
            if (i)
                printf(".");
            if (i < x)
                printf("255");
            if (i == x)
                printf("%d", ((255 << y) & 255));
            if (i > x)
                printf("0");
        }
        printf("\n");
    }
    return 0;
}