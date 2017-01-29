#include <cstdio>
#include <set>
#include <map>

using namespace std;

struct Order {
    int i, size;
    bool operator < (const Order &ord) const {
        return i < ord.i;
    }
};

map<int, set<Order>> buys, sells;

void cancel(int t) {
    for (auto it = buys.begin(); it != buys.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            if (it2->i == t) {
                it->second.erase(it2); break;
            }
        }
        if (it->second.empty()) {
            buys.erase(it); break;
        }
    }
    for (auto it = sells.begin(); it != sells.end(); ++it) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            if (it2->i == t) {
                it->second.erase(it2); break;
            }
        }
        if (it->second.empty()) {
            sells.erase(it); break;
        }
    }
}

void processorder(char c, int t, Order &tmp) {
    if (c == 'B') {
        while (!sells.empty() && sells.begin()->first <= t && tmp.size) {
            auto &ordset = sells.begin()->second;
            while (!ordset.empty() && tmp.size) {
                int size = 0, price = sells.begin()->first;
                if (tmp.size < ordset.begin()->size) {
                    Order ord = *(ordset.begin());
                    ord.size -= tmp.size;
                    ordset.erase(ordset.begin());
                    ordset.insert(ord);
                    size += tmp.size;
                    tmp.size = 0;
                }
                else {
                    tmp.size -= ordset.begin()->size;
                    size += ordset.begin()->size;
                    ordset.erase(ordset.begin());
                    if (ordset.empty()) sells.erase(price);
                }
                if (size)
                    printf("TRADE %d %d\n", size, price);
                if (!sells.count(price)) break;
            }
        }
        if (tmp.size) {
            if (!buys.count(t)) buys[t] = set<Order>();
            buys[t].insert(tmp);
        }
    }
    else {
        while (!buys.empty() && buys.rbegin()->first >= t && tmp.size) {
            auto &ordset = buys.rbegin()->second;
            while (!ordset.empty() && tmp.size) {
                int size = 0, price = buys.rbegin()->first;
                if (tmp.size < ordset.begin()->size) {
                    Order ord = *(ordset.begin());
                    ord.size -= tmp.size;
                    ordset.erase(ordset.begin());
                    ordset.insert(ord);
                    size += tmp.size;
                    tmp.size = 0;
                }
                else {
                    tmp.size -= ordset.begin()->size;
                    size += ordset.begin()->size;
                    ordset.erase(ordset.begin());
                    if (ordset.empty()) buys.erase(price);
                }
                if (size)
                    printf("TRADE %d %d\n", size, price);
                if (!buys.count(price)) break;
            }
        }
        if (tmp.size) {
            if (!sells.count(t)) sells[t] = set<Order>();
            sells[t].insert(tmp);
        }
    }
}

void print() {
    int bs, bp, as, ap;
    if (buys.size()) {
        bp = buys.rbegin()->first;
        bs = 0;
        for (auto j = buys.rbegin()->second.begin(); j != buys.rbegin()->second.end(); ++j) {
            bs += j->size;
        }
    }
    else {
        bs = bp = 0;
    }
    if (sells.size()) {
        ap = sells.begin()->first;
        as = 0;
        for (auto j = sells.begin()->second.begin(); j != sells.begin()->second.end(); ++j) {
            as += j->size;
        }
    }
    else {
        as = 0; ap = 99999;
    }
    printf("QUOTE %d %d - %d %d\n", bs, bp, as, ap);
}

int main() {
    int n, T = 0;
    Order tmp; char s[10]; int t;
    while (scanf("%d", &n) == 1) {
        if (T++) printf("\n");
        buys.clear(); sells.clear();
        for (int i = 1; i <= n; ++i) {
            scanf("%s", s);
            if (s[0] == 'C') {
                scanf("%d", &t);
                cancel(t);
            }
            else {
                scanf("%d%d", &tmp.size, &t);
                tmp.i = i;
                processorder(s[0], t, tmp);
            }
            print();
        }
    }
    return 0;
}