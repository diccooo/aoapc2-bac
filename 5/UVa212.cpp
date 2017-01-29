#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct Time {
    int h, m;
    Time (int starthour, int minutes) {
        h = starthour + minutes / 60;
        m = minutes % 60;
    }
};

struct Room {                       // room & bed
    int num, atime;
    bool operator < (const Room &r) const {
        return atime > r.atime || (atime == r.atime && num > r.num);
    }
};

struct Patient {
    char name[10];
    int i, st, rt, room ,bed, sst, rst;
    bool operator < (const Patient &p) const {
        if (sst + st != p.sst + p.st)
            return sst + st < p.sst + p.st;
        else
            return room < p.room;
    }
};

bool cmp (const Patient &p1, const Patient &p2) {
    return p1.i < p2.i;
}

vector<Patient> patients;
vector<Room> beds;
int rused[15], bused[35];

int main() {
    int rn, bn, starthour, rtob, pst, prt, pn;
    Patient ptmp; Room rtmp;
    while (scanf("%d%d%d%d%d%d%d", &rn, &bn, &starthour, &rtob, &pst, &prt, &pn) == 7) {
        patients.clear(); beds.clear();
        memset(rused, 0, sizeof(rused)); memset(bused, 0, sizeof(bused));
        priority_queue<Room> rooms;
        for (int i = 0; i < pn; ++i) {
            scanf("%s%d%d", ptmp.name, &ptmp.st, &ptmp.rt);
            ptmp.i = i + 1;
            patients.push_back(ptmp);
        }
        for (int i = 1; i <= rn; ++i) {
            rtmp.num = i; rtmp.atime = 0;
            rooms.push(rtmp);
        }
        for (int i = 0; i < pn; ++i) {
            rtmp = rooms.top();
            rooms.pop();
            patients[i].room = rtmp.num;
            patients[i].sst = rtmp.atime;
            rtmp.atime = patients[i].sst + patients[i].st + pst;
            rooms.push(rtmp);
            rused[patients[i].room] += patients[i].st;
        }
        sort(patients.begin(), patients.end());
        for (int i = 1; i <= bn; ++i) {
            rtmp.num = i; rtmp.atime = 0;
            beds.push_back(rtmp);
        }
        int endtime = 0;
        for (int i = 0; i < pn; ++i) {
            patients[i].rst = patients[i].sst + patients[i].st + rtob;
            for (int j = 0; j < bn; ++j) {
                if (patients[i].sst + patients[i].st >= beds[j].atime) {
                    patients[i].bed = beds[j].num;
                    beds[j].atime = patients[i].rst + patients[i].rt + prt;
                    bused[patients[i].bed] += patients[i].rt;
                    if (endtime < patients[i].rst + patients[i].rt)
                        endtime = patients[i].rst + patients[i].rt;
                    break;
                }
            }
        }
        sort(patients.begin(), patients.end(), cmp);
        printf(" Patient          Operating Room          Recovery Room\n");
        printf(" #  Name     Room#  Begin   End      Bed#  Begin    End\n");
        printf(" ------------------------------------------------------\n");
        for (int i = 0; i < pn; ++i) {
            Time ob(starthour, patients[i].sst), oe(starthour, patients[i].sst + patients[i].st);
            Time rb(starthour, patients[i].rst), re(starthour, patients[i].rst + patients[i].rt);
            printf("%2d  %-8s  %2d  %3d:%02d  %3d:%02d    %3d  %3d:%02d  %3d:%02d\n",
                i + 1, patients[i].name, patients[i].room, ob.h, ob.m, oe.h, oe.m, patients[i].bed, rb.h, rb.m, re.h, re.m);
        }
        printf("\n");
        printf("Facility Utilization\n");
        printf("Type  # Minutes  % Used\n");
        printf("-------------------------\n");
        for (int i = 1; i <= rn; ++i) {
            double r = 0.0;
            if (endtime) r = rused[i] * 100.0 / endtime;
            printf("Room %2d %7d %7.2lf\n", i, rused[i], r);
        }
        for (int i = 1; i <= bn; ++i) {
            double r = 0.0;
            if (endtime) r = bused[i] * 100.0 / endtime;
            printf("Bed  %2d %7d %7.2lf\n", i, bused[i], r);
        }
        printf("\n");
    }
    return 0;
}