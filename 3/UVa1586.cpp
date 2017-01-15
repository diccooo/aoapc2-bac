#include <cstdio>
#include <cstring>
#include <cctype>

#define Cm 12.01
#define Hm 1.008
#define Om 16.00
#define Nm 14.01

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        char s[85];
        scanf("%s", s);
        int sl = strlen(s);
        int num[4] = {0, 0, 0, 0};
        int i = 0, k;
        while (i < sl) {
            switch (s[i]) {
            case 'C': k = 0; break;
            case 'H': k = 1; break;
            case 'O': k = 2; break;
            case 'N': k = 3; break;
            }
            int n = 0;
            if (isdigit(s[i+1])) {
                n += s[i+1] - '0';
                ++i;
                if (isdigit(s[i+1])) {
                    n = n * 10 + s[i+1] - '0';
                    ++i;
                }
            }
            else
                ++n;
            num[k] += n;
            ++i;
        }
        double mass = Cm * num[0] + Hm * num[1] + Om * num[2] + Nm * num[3];
        printf("%.3f\n", mass);
    }
}
