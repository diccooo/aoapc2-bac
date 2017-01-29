#include <cstdio>
#include <set>

using namespace std;

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n) {
        multiset<pair<int, int>> info;
        while (n--) {
            int a, b;
            scanf("%d%d", &a, &b);
            pair<int, int> p1, p2;
            p1 = make_pair(a, b), p2 = make_pair(b, a);
            if (info.count(p2))
                info.erase(info.find(p2));
            else
                info.insert(p1);
        }
        if (info.size())
            printf("NO\n");
        else
            printf("YES\n");
    }
}