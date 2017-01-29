#include <cstdio>
#include <set>

using namespace std;

struct Point {
    int x, y;
    bool operator < (const Point &p) const {
        if (x == p.x) return y < p.y;
        else return x < p.x;
    }
};

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        int xs = 0;
        int x, y;
        set<Point> point;
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &x, &y);
            Point p;
            p.x = n * x, p.y = y;
            xs += x;
            point.insert(p);
        }
        bool f = 1;
        for (set<Point>::iterator i = point.begin(); i != point.end(); ++i) {
            Point p;
            p.y = i->y; p.x = 2 * xs - (i->x);
            if (!point.count(p)) {
                f = 0; break;
            }
        }
        if (f) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}