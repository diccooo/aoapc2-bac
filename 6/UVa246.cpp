#include <cstdio>
#include <queue>
#include <vector>
#include <set>

using namespace std;

vector<deque<int>> state;
set<vector<deque<int>>> s;

bool sum(int t, int f) {
    int c1, c2, c3, sum;
    if (f == 1) {
        c1 = state[t].front(); c2 = *(state[t].begin() + 1); c3 = state[t].back();
    }
    if (f == 2) {
        c1 = state[t].front(); c2 = *(state[t].rbegin() + 1); c3 = state[t].back();
    }
    if (f == 3) {
        c1 = *(state[t].rbegin() + 2); c2 = *(state[t].rbegin() + 1); c3 = state[t].back();
    }
    sum = c1 + c2 + c3;
    if (sum == 10 || sum == 20 || sum == 30)
        return true;
    else
        return false;
}

bool check(int t) {
    if (state[t].size() < 3)
        return false;
    int c[3]; bool f = 0;
    if (sum(t, 1)) {
        c[0] = state[t].front(); state[t].pop_front();
        c[1] = state[t].front(); state[t].pop_front();
        c[2] = state[t].back(); state[t].pop_back();
        f = 1;
    }
    else if (sum(t, 2)) {
        c[0] = state[t].front(); state[t].pop_front();
        c[2] = state[t].back(); state[t].pop_back();
        c[1] = state[t].back(); state[t].pop_back();
        f = 1;
    }
    else if (sum(t, 3)) {
        c[2] = state[t].back(); state[t].pop_back();
        c[1] = state[t].back(); state[t].pop_back();
        c[0] = state[t].back(); state[t].pop_back();
        f = 1;
    }
    if (f) {
        for (int i = 0; i < 3; ++i)
            state[0].push_back(c[i]);
        return true;
    }
    else
        return false;
}

void deal(int& t) {
    ++t;
    if (t == 8) t = 1;
    while (state[t].empty()) {
        ++t;
        if (t == 8) t = 1;
    }
    state[t].push_back(state[0].front());
    state[0].pop_front();
    for (;;) {
        if (!check(t)) break;
    }
}

int main() {
    int t;
    while (scanf("%d", &t) == 1 && t) {
        s.clear(); state.clear();
        state.resize(8);
        state[0].push_back(t);
        for (int i = 1; i < 52; ++i) {
            scanf("%d", &t);
            state[0].push_back(t);
        }
        for (int i = 1; i <= 7; ++i) {
            state[i].push_back(state[0].front());
            state[0].pop_front();
        }
        s.insert(state);
        int n = 7, t = 0;
        for (;;) {
            ++n;
            deal(t);
            if (state[0].size() == 52) {
                printf("Win : %d\n", n); break;
            }
            if (state[0].size() == 0) {
                printf("Loss: %d\n", n); break;
            }
            if (s.count(state)) {
                printf("Draw: %d\n", n); break;
            }
            s.insert(state);
        }
    }
    return 0;
}