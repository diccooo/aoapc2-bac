#include <cstdio>
#include <cstring>

char board[10][10];

bool check(char cur, int x, int y, int dx, int dy) {
    bool f = 0;
    int x0 = x, y0 = y, x1, y1;
    x += dx; y += dy;
    while (x != 0 && y != 0 && x != 9 && y != 9) {
        if (board[x][y] == cur) {
            f = 1;
            x1 = x; y1 = y;
            break;
        }
        x += dx; y += dy;
    }
    if (f) {
        int n = 0;
        x0 += dx; y0 += dy;
        while (x0 != x1 || y0 != y1) {
            if (board[x0][y0] == '-') {
                f = 0; break;
            }
            ++n;
            x0 += dx; y0 += dy;
        }
        if (n == 0)
            f = 0;
    }
    return f;
}

void list(char cur) {
    int n = 0;
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if (board[i][j] != '-')
                continue;
            bool f = 0;
            for (int dx = -1; dx <= 1; ++dx) {
                if (f) break;
                for (int dy = -1; dy <= 1; ++dy) {
                    if ((dx != 0 || dy != 0) && check(cur, i, j, dx, dy)) {
                        if (n++) printf(" ");
                        printf("(%d,%d)", i, j);
                        f = 1; break;
                    }
                }
            }
        }
    }
    if (n == 0) printf("No legal move.");
    printf("\n");
}

char move(char cur, int x, int y) {
    bool f = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        if (f) break;
        for (int dy = -1; dy <= 1; ++dy) {
            if ((dx != 0 || dy != 0) && check(cur, x, y, dx, dy)) {
                f = 1; break;
            }
        }
    }
    if (f == 0) {
        if (cur == 'W')
            cur = 'B';
        else
            cur = 'W';
    }
    board[x][y] = cur;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if ((dx != 0 || dy != 0) && check(cur, x, y, dx, dy)) {
                int x0 = x, y0 = y;
                while (board[x0 += dx][y0 += dy] != cur)
                    board[x0][y0] = cur;
            }
        }
    }
    int wn = 0, bn = 0;
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if (board[i][j] == 'W') ++wn;
            if (board[i][j] == 'B') ++bn;
        }
    }
    printf("Black - %2d White - %2d\n", bn, wn);
    if (cur == 'W')
        cur = 'B';
    else
        cur = 'W';
    return cur;
}

int main() {
    int T;
    scanf("%d", &T);
    memset(board, 0, sizeof(board));
    while (T--) {
        for (int i = 1; i <= 8; ++i) {
            scanf("%s", &board[i][1]);
        }
        char cur[2];
        scanf("%s", cur);
        char com[5];
        while (scanf("%s", com) == 1) {
            if (com[0] == 'L') {
                list(cur[0]);
            }
            if (com[0] == 'M') {
                int x = com[1] - '0', y = com[2] - '0';
                cur[0] = move(cur[0], x, y);
            }
            if (com[0] == 'Q') {
                for (int i = 1; i <= 8; ++i) {
                    for (int j = 1; j <= 8; ++j) {
                        printf("%c", board[i][j]);
                    }
                    printf("\n");
                }
                break;
            }
        }
        if (T)
            printf("\n");
    }
    return 0;
}