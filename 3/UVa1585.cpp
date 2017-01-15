#include <cstdio>
#include <cstring>

int main()
{
    int T;
    char s[85];
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        int slen = strlen(s);
        int n = 0, grade = 0;
        for (int i = 0; i < slen; ++i) {
            if (s[i] == 'O') {
                ++n;
            }
            else {
                n = 0;
            }
            grade += n;
        }
        printf("%d\n", grade);
    }
}
