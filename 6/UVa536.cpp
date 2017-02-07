#include <cstdio>
#include <cstring>

const int maxn = 30;

char prestr[maxn], instr[maxn];

void convert(int p1, int p2, int i1, int i2) {
    if (p1 == p2 && i1 == i2) return;
    if (p2 - p1 == 1 && i2 - i1 == 1) {
        printf("%c", prestr[p1]); return;
    }
    char r = prestr[p1];
    int rp = strchr(instr, r) - instr;
    convert(p1 + 1, p1 + 1 + rp - i1, i1, rp);
    convert(p1 + 1 + rp - i1, p2, rp + 1, i2);
    printf("%c", r);
}

int main() {
    while (scanf("%s%s", prestr, instr) == 2) {
        int len = strlen(prestr);
        convert(0, len, 0, len);
        printf("\n");
    }
    return 0;
}