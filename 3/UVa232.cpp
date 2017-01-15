#include <cstdio>
#include <cstring>

int main()
{
    int r, c;
    int t = 0;
    while(scanf("%d", &r) == 1) {
        ++t;
        if (r == 0)
            break;
        scanf("%d", &c);
        char grid[12][12];
        memset(grid, 0, sizeof(grid));
        for (int i = 0; i < r; ++i) {
            scanf("%s", grid[i]);
        }
        int gridnum[12][12];
        memset(gridnum, 0, sizeof(gridnum));
        int num = 1;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                bool flag = ((i == 0 || j == 0) || (grid[i - 1][j] == '*' || grid[i][j - 1] == '*')) && (grid[i][j] != 0 && grid[i][j] != '*');
                if (flag) {
                    gridnum[i][j] = num++;
                }
            }
        }
        if (t - 1)
            printf("\n");
        printf("puzzle #%d:\n", t);
        printf("Across\n");
        int i = 0;
        while (i < r) {
            int j = 0;
            while (j < c) {
                if (gridnum[i][j] != 0) {
                    printf("%3d.", gridnum[i][j]);
                    for (int k = j; k < c; ++k) {
                        if (grid[i][k] == '*' || grid[i][k] == 0) break;
                        printf("%c", grid[i][k]);
                        j = k;
                    }
                    printf("\n");
                }
                ++j;
            }
            ++i;
        }
        printf("Down\n");
        i = 0;
        while (i < r) {
            int j = 0;
            while (j < c) {
                if (gridnum[i][j] != 0 && (i == 0 || grid[i - 1][j] == '*')) {
                    printf("%3d.", gridnum[i][j]);
                    for (int k = i; k < r; ++k) {
                        if (grid[k][j] == '*' || grid[k][j] == 0) break;
                        printf("%c", grid[k][j]);
                    }
                    printf("\n");
                }
                ++j;
            }
            ++i;
        }
    }
    return 0;
}
