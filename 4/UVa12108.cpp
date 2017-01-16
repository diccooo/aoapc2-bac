#include <cstdio>

struct Student {
    int a, b, c;
    int stat[12];
} students[12];

bool isAllAwaken(int *status, Student *students, int T) {
    for (int i = 0; i < T; ++i) {
        if (students[i].stat[status[i]])
            return false;
    }
    return true;
}

bool isSameAsBegin(int *status, Student *students, int T) {
    for (int i = 0; i < T; ++i) {
        if (status[i] != students[i].c)
            return false;
    }
    return true;
}

void update(int *status, Student *students, int T) {
    int n = 0;
    for (int i = 0; i < T; ++i) {
        if (students[i].stat[status[i]])
            ++n;
    }
    for (int i = 0; i < T; ++i) {
        if (status[i] == students[i].a + students[i].b) {
            status[i] = 1;
        }
        else if (status[i] == students[i].a) {
            if (n > T - n)
                ++status[i];
            else
                status[i] = 1;
        }
        else
            ++status[i];
    }
}

int main() {
    int T, n = 0;
    while (scanf("%d", &T) == 1 && T) {
        for (int i = 0; i < T; ++i) {
            scanf("%d%d%d", &students[i].a, &students[i].b, &students[i].c);
            for (int j = 1; j <= students[i].a; ++j)
                students[i].stat[j] = 0;
            for (int j = 1; j <= students[i].b; ++j)
                students[i].stat[students[i].a + j] = 1;
        }
        int status[12] = {0};
        for (int i = 0; i < T; ++i)
            status[i] = students[i].c;
        int t = 1;
        for(;;) {
            if (isAllAwaken(status, students, T)) break;
            if (t != 1 && isSameAsBegin(status, students, T)) {
                t = -1; break;
            }
            update(status, students, T);
            ++t;
        }
        printf("Case %d: %d\n", ++n, t);
    }
    return 0;
}