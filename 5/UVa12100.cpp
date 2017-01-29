#include <cstdio>
#include <queue>

using namespace std;

struct Task {
    int priority;
    bool mine;
};

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        deque<Task> tq;
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i) {
            Task t;
            scanf("%d", &t.priority);
            if (i == m) t.mine = 1;
            else t.mine = 0;
            tq.push_back(t);
        }
        int time = 0;
        for (;;) {
            Task t = tq.front();
            bool f = 0;
            for (auto i = tq.begin() + 1; i != tq.end(); ++i) {
                if (i->priority > t.priority) {
                    tq.push_back(t);
                    tq.pop_front();
                    f = 1;
                    break;
                }
            }
            if (f) continue;
            tq.pop_front();
            ++time;
            if (t.mine) {
                printf("%d\n", time);
                break;
            }
        }
    }
    return 0;
}