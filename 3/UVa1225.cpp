#include <cstdio>

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        int num[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (int i = 1; i <= n; ++i) {
            int p = i;
            while (p) {
                num[p % 10]++;
                p /= 10;
            }
        }
        for (int i = 0; i < 9; ++i) {
            printf("%d ", num[i]);
        }
        printf("%d\n", num[9]);
    }
}
