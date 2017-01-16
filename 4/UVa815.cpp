#include <cstdio>
#include <algorithm>

int elev[1000];

int main() {
    int m, n, water, T = 0;
    while (scanf("%d%d", &m, &n) == 2 && m) {
        m *= n;
        for (int i = 0; i < m; ++i) {
                scanf("%d", &elev[i]);
        }
        elev[m] = (1 << 30);
        scanf("%d", &water);
        double w = water / 100.0;
        std::sort(elev, elev + m);
        int i;
        for (i = 0; i < m; ++i) {
            w += elev[i];
            if (w / (i + 1) <= elev[i + 1]) {
                break;
            }
        }
        printf("Region %d\n", ++T);
        printf("Water level is %.2lf meters.\n", w / (i + 1));
        printf("%.2lf percent of the region is under water.\n\n", 100.0 * (i + 1) / m);
    }
    return 0;
}