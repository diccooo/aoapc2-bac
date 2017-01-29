#include <cstdio>
#include <deque>

using namespace std;

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n) {
        deque<int> q;
        for (int i = 1; i <= n; ++i)
            q.push_back(i);
        printf("Discarded cards:");
        for (int i = 0; i < n - 1; ++i) {
            if (i) printf(",");
            printf(" %d", q.front());
            q.pop_front();
            q.push_back(q.front());
            q.pop_front();
        }
        printf("\nRemaining card: %d\n", q.front());
    }
    return 0;
}