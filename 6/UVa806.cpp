#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxn = 70;

int img[maxn][maxn];
vector<int> paths;
int T = 0;

void inputimg(int n) {
    char s[maxn];
    for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        for (int j = 0; j < n; ++j)
            img[i][j] = s[j] - '0';
    }
}

void inputpath() {
    paths.clear();
    int d;
    while (scanf("%d", &d) == 1 && d != -1)
        paths.push_back(d);
}

bool issame(int &oz, int r, int c, int w) {
    oz = img[r][c];
    for (int i = r; i < r + w; ++i)
        for (int j = c; j < c + w; ++j)
            if (img[i][j] != oz)
                return false;
    return true;
}

void itop(int r, int c, int w, int pow5d, int pn) {
    int oz;
    if (issame(oz, r, c, w)) {
        if (oz == 1) {
            paths.push_back(pn);
        }
        return;
    }
    itop(r, c, w / 2, 5 * pow5d, 1 * pow5d + pn);
    itop(r, c + w / 2, w / 2, 5 * pow5d, 2 * pow5d + pn);
    itop(r + w / 2, c, w / 2, 5 * pow5d, 3 * pow5d + pn);
    itop(r + w / 2, c + w / 2, w / 2, 5 * pow5d, 4 * pow5d + pn);
}

void imgtopath(int n) {
    paths.clear();
    int oz;
    if (issame(oz, 0, 0, n)) {
        if (oz == 1)
            paths.push_back(0);
        return;
    }
    itop(0, 0, n / 2, 5, 1);
    itop(0, n / 2, n / 2, 5, 2);
    itop(n / 2, 0, n / 2, 5, 3);
    itop(n / 2, n / 2, n / 2, 5, 4);
}

void draw(int r, int c, int w) {
    for (int i = r; i < r + w; ++i)
        for (int j = c; j < c + w; ++j)
            img[i][j] = 1;
}

void ptoi(int r, int c, int w, int p) {
    if (p == 1) draw(r, c, w / 2);
    else if (p == 2) draw(r, c + w / 2, w / 2);
    else if (p == 3) draw(r + w / 2, c, w / 2);
    else if (p == 4) draw(r + w / 2, c + w / 2, w / 2);
    else {
        int a = p / 5, b = p % 5;
        if (b == 1) ptoi(r, c, w / 2, a);
        if (b == 2) ptoi(r, c + w / 2, w / 2, a);
        if (b == 3) ptoi(r + w / 2, c, w / 2, a);
        if (b == 4) ptoi(r + w / 2, c + w / 2, w / 2, a);
    }
}

void pathtoimg(int n) {
    memset(img, 0, sizeof(img));
    if (paths.empty()) return;
    for (auto it = paths.begin(); it != paths.end(); ++it) {
        if (*it == 0) {
            draw(0, 0, n);
        }
        else
            ptoi(0, 0, n, *it);
    }
}

void printpath() {
    if (T) printf("\n");
    printf("Image %d\n", ++T);
    if (paths.size()) {
        sort(paths.begin(), paths.end());
        for (int i = 0; i < paths.size(); ++i) {
            if (i && i % 12 != 0) printf(" ");
            printf("%d", paths[i]);
            if ((i + 1) % 12 == 0 && i + 1 != paths.size()) printf("\n");
        }
        printf("\n");
    }
    printf("Total number of black nodes = %d\n", paths.size());
}

void printimg(int n) {
    if (T) printf("\n");
    printf("Image %d\n", ++T);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (img[i][j] == 0) printf(".");
            else printf("*");
        }
        printf("\n");
    }
}

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n) {
        if (n > 0) {
            inputimg(n);
            imgtopath(n);
            printpath();
        }
        else {
            inputpath();
            pathtoimg(-n);
            printimg(-n);
        }
    }
    return 0;
}