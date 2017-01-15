#include <cstdio>
#include <cstring>

struct Piece {
    char kind[2];
    int x, y;
} redp[7];

bool check[10][10];

int main() {
    int n;
    int bx, by;
    while (scanf("%d", &n) == 1 && n) {
        scanf("%d%d", &bx, &by);
        for (int i = 0; i < n; ++i) {
            scanf("%s%d%d", redp[i].kind, &redp[i].x, &redp[i].y);
        }
        memset(check, 0, sizeof(check));
        for (int i = 3; i <= 7; ++i)
            check[0][i] = check[4][i] = 1;
        for (int i = 1; i <= 3; ++i)
            check[i][3] = check[i][7] = 1;
        for (int i = 0; i < n; ++i) {
            if (redp[i].kind[0] == 'G') {
                int mx = 0;
                for (int j = 0; j < n; ++j) {
                    if (j != i && redp[j].y == redp[i].y) {
                        if (mx < redp[j].x)
                            mx = redp[j].x;
                    }
                }
                for (int j = mx; j <= 3; ++j)
                    check[j][redp[i].y] = 1;
            }
            if (redp[i].kind[0] == 'R') {
                int x1 = 1, x2 = 10, y1 = 1, y2 = 9;
                for (int j = 0; j < n; ++j) {
                    if (j != i) {
                        if (redp[j].x == redp[i].x) {
                            if (redp[j].y < redp[i].y && redp[j].y > y1)
                                y1 = redp[j].y;
                            if (redp[j].y > redp[i].y && redp[j].y < y2)
                                y2 = redp[j].y;
                        }
                        if (redp[j].y == redp[i].y) {
                            if (redp[j].x < redp[i].x && redp[j].x > x1)
                                x1 = redp[j].x;
                            if (redp[j].x > redp[j].x && redp[j].x < x2)
                                x2 = redp[j].x;
                        }
                    }
                }
                while (x1 < redp[i].x)
                    check[x1++][redp[i].y] = 1;
                while (x2 > redp[i].x)
                    check[x2--][redp[i].y] = 1;
                while (y1 < redp[i].y)
                    check[redp[i].x][y1++] = 1;
                while (y2 > redp[i].y)
                    check[redp[i].x][y2--] = 1;
            }
            if (redp[i].kind[0] == 'C') {
                int x1 = 1, x2 = 10, y1 = 1, y2 = 9;
                for (int j = 0; j < n; ++j) {
                    if (j != i) {
                        if (redp[j].x == redp[i].x) {
                            if (redp[j].y < redp[i].y && redp[j].y > y1)
                                y1 = redp[j].y;
                            if (redp[j].y > redp[i].y && redp[j].y < y2)
                                y2 = redp[j].y;
                        }
                        if (redp[j].y == redp[i].y) {
                            if (redp[j].x < redp[i].x && redp[j].x > x1)
                                x1 = redp[j].x;
                            if (redp[j].x > redp[j].x && redp[j].x < x2)
                                x2 = redp[j].x;
                        }
                    }
                }
                while (--x1 >= 0) {
                    check[x1][redp[i].y] = 1;
                    bool flag = 0;
                    for (int j = 0; j < n; ++j)
                        if (redp[j].x == x1 && redp[j].y == redp[i].y) {
                            flag = 1; break;
                        }
                    if (flag) break;
                }
                while (++x2 <= 10) {
                    check[x2][redp[i].y] = 1;
                    bool flag = 0;
                    for (int j = 0; j < n; ++j)
                        if (redp[j].x == x2 && redp[j].y == redp[i].y) {
                            flag = 1; break;
                        }
                    if (flag) break;
                }
                while (--y1 >= 0) {
                    check[redp[i].x][y1] = 1;
                    bool flag = 0;
                    for (int j = 0; j < n; ++j)
                        if (redp[j].x == redp[i].x && redp[j].y == y1) {
                            flag = 1; break;
                        }
                    if (flag) break;
                }
                while (++y2 <= 9) {
                    check[redp[i].x][y2] = 1;
                    bool flag = 0;
                    for (int j = 0; j < n; ++j)
                        if (redp[j].x == redp[i].x && redp[j].y == y2) {
                            flag = 1; break;
                        }
                    if (flag) break;
                }
            }
            if (redp[i].kind[0] == 'H') {
                bool up = 1, down = 1, left = 1, right = 1;
                for (int j = 0; j < n; ++j) {
                    if (j != i) {
                        if (redp[j].x == redp[i].x) {
                            if (redp[j].y == redp[i].y - 1)
                                left = 0;
                            if (redp[j].y == redp[i].y + 1)
                                right = 0;
                        }
                        if (redp[j].y == redp[i].y) {
                            if (redp[j].x == redp[i].x - 1)
                                up = 0;
                            if (redp[j].x == redp[i].x + 1)
                                down = 0;
                        }
                    }
                }
                if (up && redp[i].x - 2 > 0) {
                    if (redp[i].y - 1 > 0)
                        check[redp[i].x - 2][redp[i].y - 1] = 1;
                    if (redp[i].y + 1 < 10)
                        check[redp[i].x - 2][redp[i].y + 1] = 1;
                }
                if (down && redp[i].x + 2 <= 10) {
                    if (redp[i].y - 1 > 0)
                        check[redp[i].x + 2][redp[i].y - 1] = 1;
                    if (redp[i].y + 1 < 10)
                        check[redp[i].x + 2][redp[i].y + 1] = 1;
                }
                if (left && redp[i].y - 2 > 0) {
                    if (redp[i].x - 1 > 0)
                        check[redp[i].x - 1][redp[i].y - 2] = 1;
                    if (redp[i].x + 1 <= 10)
                        check[redp[i].x + 1][redp[i].y - 2] = 1;
                }
                if (right && redp[i].y + 2 > 0) {
                    if (redp[i].x - 1 > 0)
                        check[redp[i].x - 1][redp[i].y + 2] = 1;
                    if (redp[i].x + 1 <= 10)
                        check[redp[i].x + 1][redp[i].y + 2] = 1;
                }
            }
        }
        if (check[bx + 1][by] && check[bx - 1][by] && check[bx][by - 1] && check[bx][by + 1])
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}