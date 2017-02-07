#include <cstdio>
#include <cstring>
#include <map>
#include <vector>

using namespace std;

const int maxn = 100 + 5;

struct Trans {
    map<int, int> in, out;
} trans[maxn];

int np, nt, nf;
int places[maxn];

bool isenabled(int i) {
    for (auto it = trans[i].in.begin(); it != trans[i].in.end(); ++it) {
        if (places[it->first] < it->second)
            return false;
    }
    return true;
}

void fire(int i) {
    for (auto it = trans[i].in.begin(); it != trans[i].in.end(); ++it) {
        places[it->first] -= it->second;
    }
    for (auto it = trans[i].out.begin(); it != trans[i].out.end(); ++it) {
        places[it->first] += it->second;
    }
}

int main() {
    int T = 0;
    while (scanf("%d", &np) == 1 && np) {
        memset(places, 0, sizeof(places));
        for (int i = 1; i <= np; ++i)
            scanf("%d", &places[i]);
        scanf("%d", &nt);
        int tmp;
        for (int i = 1; i <= nt; ++i) {
            trans[i].in.clear(); trans[i].out.clear();
            while (scanf("%d", &tmp) == 1 && tmp) {
                if (tmp < 0) {
                    tmp = -tmp;
                    if (!trans[i].in.count(tmp))
                        trans[i].in[tmp] = 1;
                    else
                        trans[i].in[tmp]++;
                }
                else {
                    if (!trans[i].out.count(tmp))
                        trans[i].out[tmp] = 1;
                    else
                        trans[i].out[tmp]++;
                }
            }
        }
        scanf("%d", &nf);

        int num = 0;
        while (num < nf) {
            bool f = 1;
            for (int i = 1; i <= nt; ++i) {
                if (isenabled(i)) {
                    f = 0; fire(i); break;
                }
            }
            if (f) break;
            ++num;
        }

        printf("Case %d: ", ++T);
        if (num < nf) printf("dead after %d transitions\n", num);
        else printf("still live after %d transitions\n", nf);
        printf("Places with tokens:");
        for (int i = 1; i <= np; ++i) {
            if (places[i])
                printf(" %d (%d)", i, places[i]);
        }
        printf("\n\n");
    }
    return 0;
}