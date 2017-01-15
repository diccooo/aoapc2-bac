#include <cstdio>
#include <cstring>

int u[3010];
int r[3010];

int main()
{
    int a, b;
    while(scanf("%d%d", &a, &b) == 2) {
        printf("%d/%d = %d.", a, b, a/b);
        memset(u, 0, sizeof(u));
        memset(r, 0, sizeof(r));
        int start = -1, end = -1;
        for (int i = 0; i < 3010; ++i) {
            a = a % b;
            a *= 10;
            u[i] = a;
            r[i] = u[i] / b;
            for (int j = 0; j < i; ++j) {
                if (u[i] == u[j]) {
                    start = j;
                    end = i;
                }
            }
            if (start != -1 && end != -1)
                break;
        }
        for (int i = 0; i < start; ++i)
            printf("%d", r[i]);
        printf("(");
        for (int i = start; i < end && i < start + 50; ++i)
            printf("%d", r[i]);
        if (end - start > 50)
            printf("...");
        printf(")\n");
        printf("   %d = number of digits in repeating cycle\n\n", end - start);
    }
    return 0;
}