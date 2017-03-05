#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, -1, 0, 1};         // up, left, down, right
const int rightside[7][7] = {{0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 3, 5, 2, 4, 0}, {0, 4, 0, 1, 6, 0, 3}, {0, 2, 6, 0, 0, 1, 5},
                             {0, 5, 1, 0, 0, 6, 2}, {0, 3, 0, 6, 1, 0, 4}, {0, 0, 4, 2, 5, 3, 0}};

struct Node {
    int r, c, td, fd;
    Node(int r = 0, int c = 0, int td = 0, int fd = 0): r(r), c(c), td(td), fd(fd) {}
};

int maze[15][15];
int visited[15][15][7][7];                // r, c, td, fd
Node p[15][15][7][7];
int r, c, sr, sc, td, fd;

void tip(int &t, int &f, int drct) {
    int tmp;
    if (drct == 0) {
        tmp = t; t = f; f = 7 - tmp;
    }
    else if (drct == 1) {
        t = rightside[t][f];
    }
    else if (drct == 2) {
        tmp = f; f = t; t = 7 - tmp;
    }
    else if (drct == 3) {
        t = 7 - rightside[t][f];
    }
}

inline bool isvalid(Node &u, int i) {
    int t = maze[u.r + dr[i]][u.c + dc[i]];
    return t != 0 && (t == -1 || t == u.td);
}

void print(Node u) {
    vector<Node> nodes;
    nodes.push_back(u);
    u = p[u.r][u.c][u.td][u.fd];
    for (;;) {
        nodes.push_back(u);
        if (u.r == sr && u.c == sc) break;
        u = p[u.r][u.c][u.td][u.fd];
    }
    int cnt = 0;
    for (auto it = nodes.rbegin(); it != nodes.rend(); ++it) {
        if (cnt % 9 == 0) printf("  ");
        printf("(%d,%d)", it->r, it->c);
        if (it != nodes.rend() - 1) printf(",");
        if (++cnt % 9 == 0) printf("\n");
    }
    if (nodes.size() % 9 != 0) printf("\n");
}

void bfs() {
    queue<Node> q;
    memset(visited, 0, sizeof(visited));
    Node u(sr, sc, td, fd);
    q.push(u);
    while (!q.empty()) {
        Node u = q.front(); q.pop();
        //printf("%d %d %d %d\n", u.r, u.c, u.td, u.fd);
        if (u.r == sr && u.c == sc && visited[u.r][u.c][u.td][u.fd]) {
            print(u); return;
        }
        for (int i = 0; i < 4; ++i) {
            if (isvalid(u, i)) {
                int t = u.td, f = u.fd;
                tip(t, f, i);
                Node v(u.r + dr[i], u.c + dc[i], t, f);
                if (!visited[v.r][v.c][v.td][v.fd]) {
                    visited[v.r][v.c][v.td][v.fd] = 1;
                    p[v.r][v.c][v.td][v.fd] = u;
                    q.push(v);
                }
            }
        }
    }
    printf("  No Solution Possible\n");
}

int main() {
    char name[25];
    while (scanf("%s", name) == 1 && strcmp(name, "END")) {
        scanf("%d%d%d%d%d%d", &r, &c, &sr, &sc, &td, &fd);
        memset(maze, 0, sizeof(maze));
        for (int i = 1; i <= r; ++i)
            for (int j = 1; j <= c; ++j)
                scanf("%d", &maze[i][j]);
        printf("%s\n", name);
        bfs();
    }
    return 0;
}