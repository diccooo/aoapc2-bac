#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Map {
    string name;
    double x1, x2, y1, y2;
    double area;
};

struct Location {
    string name;
    double x, y;
};

struct Maplvl {
    int locnum, mapnum, lvl;
};

vector<Map> maps;
vector<Location> locs;
vector<vector<Maplvl>> locmap; 

bool cmp(const Maplvl &m1, const Maplvl &m2) {
    if (maps[m1.mapnum].area != maps[m2.mapnum].area)
        return maps[m1.mapnum].area < maps[m2.mapnum].area;
    else {
        double c1x = (maps[m1.mapnum].x1 + maps[m1.mapnum].x2) / 2;
        double c1y = (maps[m1.mapnum].y1 + maps[m1.mapnum].y2) / 2;
        double c2x = (maps[m2.mapnum].x1 + maps[m2.mapnum].x2) / 2;
        double c2y = (maps[m2.mapnum].y1 + maps[m2.mapnum].y2) / 2;
        double d1 = pow(c1x - locs[m1.locnum].x, 2) + pow(c1y - locs[m1.locnum].y, 2);
        double d2 = pow(c2x - locs[m2.locnum].x, 2) + pow(c2y - locs[m2.locnum].y, 2);
        if (d1 != d2)
            return d1 < d2;
        else {
            d1 = abs((maps[m1.mapnum].y2 - maps[m1.mapnum].y1) / (maps[m1.mapnum].x2 - maps[m1.mapnum].x1) - 0.75);
            d2 = abs((maps[m2.mapnum].y2 - maps[m2.mapnum].y1) / (maps[m2.mapnum].x2 - maps[m2.mapnum].x1) - 0.75);
            if (d1 != d2)
                return d1 < d2;
            else {
                d1 = pow(maps[m1.mapnum].x2 - locs[m1.mapnum].x, 2) + pow(maps[m1.mapnum].y2 - locs[m1.mapnum].y, 2);
                d2 = pow(maps[m2.mapnum].x2 - locs[m2.mapnum].x, 2) + pow(maps[m2.mapnum].y2 - locs[m2.mapnum].y, 2);
                if (d1 != d2)
                    return d1 > d2;
                else {
                    return maps[m1.mapnum].x1 < maps[m2.mapnum].x2;
                }
            }
        }
    }
}

void readmap() {
    string s;
    cin >> s;
    while (cin >> s && s != "LOCATIONS") {
        double x1, y1, x2, y2;
        cin >> x1; cin >> y1; cin >> x2; cin >> y2;
        Map m;
        m.name = s;
        if (x1 < x2) {
            m.x1 = x1; m.x2 = x2;
        }
        else {
            m.x1 = x2; m.x2 = x1;
        }
        if (y1 < y2) {
            m.y1 = y1; m.y2 = y2;
        }
        else {
            m.y1 = y2; m.y2 = y1;
        }
        m.area = (m.x2 - m.x1) * (m.y2 - m.y1);
        maps.push_back(m);
    }
}

void readlocation() {
    string s;
    int n = -1;
    while (cin >> s && s != "REQUESTS") {
        ++n;
        double x, y;
        cin >> x; cin >> y;
        Location loc;
        loc.name = s;
        loc.x = x; loc.y = y;
        locs.push_back(loc);
        vector<Maplvl> ml;
        for (int i = 0; i < maps.size(); ++i) {
            if (x >= maps[i].x1 && x <= maps[i].x2 && y >= maps[i].y1 && y <= maps[i].y2) {
                Maplvl t;
                t.locnum = n; t.mapnum = i;
                ml.push_back(t);
            }
        }
        sort(ml.begin(), ml.end(), cmp);
        double a = 0;
        int lvl = 0;
        for (auto i = ml.rbegin(); i != ml.rend(); ++i) {
            if (maps[i->mapnum].area != a) {
                a = maps[i->mapnum].area;
                ++lvl;
            }
            i->lvl = lvl;
        }
        locmap.push_back(ml);
    }
}

void echorequest() {
    string s;
    while (cin >> s && s != "END") {
        int lvl;
        cin >> lvl;
        cout << s << " at detail level " << lvl;
        int i;
        for (i = 0; i < locs.size(); ++i) {
            if (locs[i].name == s)
                break;
        }
        if (i == locs.size()) {
            cout << " unknown location\n"; continue;
        }
        if (locmap[i].empty()) {
            cout << " no map contains that location\n"; continue;
        }
        for (auto j = locmap[i].begin(); j != locmap[i].end(); ++j) {
            if (j->lvl == lvl) {
                cout << " using " << maps[j->mapnum].name << endl;
                break;
            }
            if (j->lvl < lvl) {
                cout << " no map at that detail level; using " << maps[j->mapnum].name << endl;
                break;
            }
        }
    }
}

int main() {
    readmap();
    readlocation();
    echorequest();
    return 0;
}