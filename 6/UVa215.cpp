#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>
#include <queue>

using namespace std;

struct Cell;

struct Edge {
    int op;
    Cell *cell;
};

struct Cell {
    string exp;
    bool isvalue;
    int v;
    vector<Edge> ref;
    vector<Cell*> berefed;
};

int r, c;
Cell sheet[25][15];

void init() {
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            Cell &t = sheet[i][j];
            t.v = 0;
            t.ref.clear(); t.berefed.clear();
        }
    }
}

bool isvalue(string &s) {
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (isalpha(*it)) return false;
    }
    return true;
}

void parse(string &s, int i, int j) {
    Cell &t = sheet[i][j];
    t.exp = s;
    vector<string> exp;
    size_t start = 0, end = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '+' || s[i] == '-') {
            end = i;
            if (end > start)
                exp.push_back(s.substr(start, end - start));
            start = end;
        }
    }
    exp.push_back(s.substr(start));
    int tmp;
    for (auto it = exp.begin(); it != exp.end(); ++it) {
        if (isvalue(*it)) {
            stringstream ss(*it);
            ss >> tmp;
            t.v += tmp;
        }
        else {
            Edge e;
            if (it->size() == 2) e.op = 1;
            else {
                if ((*it)[0] == '+') e.op = 1;
                else e.op = -1;
            }
            char c2 = *it->rbegin() - '0', c1 = *(it->rbegin() + 1) - 'A';
            e.cell = &sheet[c1][c2];
            t.ref.push_back(e);
            sheet[c1][c2].berefed.push_back(&sheet[i][j]);
        }
    }
    if (t.ref.size()) t.isvalue = 0;
    else t.isvalue = 1;
}

void calc() {
    queue<Cell*> q;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (sheet[i][j].isvalue && sheet[i][j].berefed.size())
                q.push(&sheet[i][j]);
        }
    }
    while (!q.empty()) {
        Cell *u = q.front(); q.pop();
        for (auto it = u->berefed.begin(); it != u->berefed.end(); ++it) {
            Cell *v = *it;
            for (auto it2 = v->ref.begin(); it2 != v->ref.end(); ++it2) {
                if (it2->cell == u) {
                    v->v += (it2->op) * (u->v);
                    v->ref.erase(it2);
                    break;
                }
            }
            if (v->ref.empty()) {
                v->isvalue = 1;
                q.push(v);
            }
        }
        u->berefed.clear();
    }
}

void print() {
    vector<pair<int, int>> p;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (!sheet[i][j].isvalue) {
                p.push_back(make_pair(i, j));
            }
        }
    }
    if (p.empty()) {
        printf(" ");
        for (int i = 0; i < c; ++i)
            printf("%6d", i);
        printf("\n");
        for (int i = 0; i < r; ++i) {
            printf("%c", 'A' + i);
            for (int j = 0; j < c; ++j)
                printf("%6d", sheet[i][j].v);
            printf("\n");
        }
    }
    else {
        for (auto it = p.begin(); it != p.end(); ++it) {
            printf("%c%d: %s\n", it->first + 'A', it->second, sheet[it->first][it->second].exp.c_str());
        }
    }
    printf("\n");
}

int main() {
    string s;
    while ((cin >> r >> c) && r && c) {
        init();
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                cin >> s;
                parse(s, i, j);
            }
        }
        calc();
        print();
    }
    return 0;
}