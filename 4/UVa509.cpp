#include <cstdio>
#include <cstring>

const char hex[] = "0123456789ABCDEF";
int bits[10][105][80];
char data[10000];

bool isvalid(int d, int s, int b, int parity) {
    for (int i = 0; i < b; ++i) {
        for (int j = 0; j < s; ++j) {
            int xn = 0;
            for (int k = 0; k < d; ++k) {
                if (bits[k][i][j] == -1) {
                    ++xn;
                    if (xn > 1) return false;
                }
            }
            if (!xn) {
                int x = bits[0][i][j];
                for (int k = 1; k < d; ++k) {
                    x ^= bits[k][i][j];
                }
                if (x != parity) return false;
            }
        }
    }
    return true;
}

void recover(int d, int s, int b, int parity) {
    memset(data, 0, sizeof(data));
    for (int i = 0; i < b; ++i) {
        for (int j = 0; j < s; ++j) {
            int xk = -1, x = parity;
            for (int k = 0; k < d; ++k) {
                if (bits[k][i][j] == -1)
                    xk = k;
                else
                    x ^= bits[k][i][j];
            }
            if (xk != -1)
                bits[xk][i][j] = x;
        }
    }
    int di = -1, bi = -1, m = 0;
    int hexbit[4] = {0};
    for (int i = 0; i < b; ++i) {
        di = (di + 1) % d;
        for (int j = 0; j < d; ++j) {
            if (j == di) continue;
            for (int k = 0; k < s; ++k) {
                bi = (bi + 1) % 4;
                hexbit[bi] = bits[j][i][k];
                if (bi == 3) {
                    data[m++] = hex[(hexbit[0] << 3) + (hexbit[1] << 2) + (hexbit[2] << 1) + hexbit[3]];
                    hexbit[0] = 0, hexbit[1] = 0, hexbit[2] = 0, hexbit[3] = 0;
                }
            }
        }
    }
    if (bi != 3) {
        data[m++] = hex[(hexbit[0] << 3) + (hexbit[1] << 2) + (hexbit[2] << 1) + hexbit[3]];
    }
}

int main() {
    int d, s, b, T = 0;
    char ptype[2];
    while (scanf("%d", &d) == 1 && d != 0) {
        ++T;
        scanf("%d%d%s", &s, &b, ptype);
        getchar();
        for (int i = 0; i < d; ++i) {
            for (int j = 0; j < b; ++j) {
                for (int k = 0; k < s; ++k) {
                    char c = getchar();
                    if (c == 'x') bits[i][j][k] = -1;
                    else bits[i][j][k] = c - '0';
                }
            }
            getchar();
        }
        int parity;
        if (ptype[0] == 'E') parity = 0;
        else parity = 1;
        if (!isvalid(d, s, b, parity))
            printf("Disk set %d is invalid.\n", T);
        else {
            recover(d, s, b, parity);
            printf("Disk set %d is valid, contents are: %s\n", T, data);
        }
    }
    return 0;
}