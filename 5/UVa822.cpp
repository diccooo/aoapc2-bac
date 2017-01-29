#include <cstdio>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

const int inf = 1 << 30;

struct Request {
    int t;
    queue<int> time;
};

struct Personnel {
    int id, k, last, fin, tid[25];
    bool operator < (const Personnel &p) const {
        return last < p.last || (last == p.last && id < p.id);
    }
};

map<int, Request> reqs;
vector<Personnel> persons;

int main() {
    int T = 0, qn, pn;
    while (scanf("%d", &qn) == 1 && qn) {
        ++T;
        int t = inf, fin = 0;
        reqs.clear(); persons.clear();
        for (int i = 0; i < qn; ++i) {
            Request req;
            int id, num, t0, dt;
            scanf("%d%d%d%d%d", &id, &num, &t0, &req.t, &dt);
            if (t > t0) t = t0;
            for (int j = 0; j < num; ++j) {
                req.time.push(t0 + j * dt);
            }
            reqs[id] = req;
        }
        scanf("%d", &pn);
        for (int i = 0; i < pn; ++i) {
            Personnel p;
            scanf("%d%d", &p.id, &p.k);
            for (int j = 0; j < p.k; ++j) {
                scanf("%d", &p.tid[j]);
            }
            p.last = p.fin = 0;
            persons.push_back(p);
        }
        while (qn) {
            sort(persons.begin(), persons.end());
            int nextt = inf;
            for (auto i = persons.begin(); i != persons.end(); ++i) {
                int pnextt = inf;
                if (i->fin > t)
                    pnextt = i->fin;
                else {
                    for (int j = 0; j < i->k; ++j) {
                        auto &r = reqs[i->tid[j]];
                        if (r.time.empty()) continue;
                        if (r.time.front() > t) {
                            if (r.time.front() < pnextt)
                                pnextt = r.time.front();
                            continue;
                        }
                        i->last = t;
                        pnextt = i->fin = t + r.t;
                        r.time.pop();
                        if (r.time.empty()) --qn;
                        if (fin < i->fin) fin = i->fin;
                        break;
                    }
                }
                if (pnextt < nextt) nextt = pnextt;
            }
            t = nextt;
        }
        printf("Scenario %d: All requests are serviced within %d minutes.\n", T, fin);
    }
    return 0;
}