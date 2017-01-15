#include <cstdio>

char s[100000], t[100000];

int main()
{
    while (scanf("%s%s", s, t) == 2) {
        char *sp = s, *tp = t;
        while (*sp && *tp) {
            if (*sp == *tp) {
                ++sp; ++tp;
            }
            else
                ++tp;
        }
        if (!*sp)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}