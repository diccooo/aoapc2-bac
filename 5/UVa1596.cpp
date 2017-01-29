#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <cctype>

using namespace std;

struct ArrInd {
    int len;
    map<int, int> assigned;
};
map<string, ArrInd> arr;

void readremain() {
    string s;
    while (cin >> s && s != ".");
}

void parsedec(const string &s) {
    auto pos1 = s.find_first_of('['), pos2 = s.find_last_of(']');
    string arrname = s.substr(0, pos1);
    string length = s.substr(pos1 + 1, pos2 - pos1 - 1);
    stringstream ss(length);
    ArrInd a;
    ss >> a.len;
    arr[arrname] = a;
}

bool checkrval(const string &s, int &rval) {
    if (isdigit(s[0])) {
        stringstream ss(s);
        ss >> rval;
        return true;
    }
    auto pos1 = s.find_first_of('['), pos2 = s.find_last_of(']');
    string arrname = s.substr(0, pos1);
    string index = s.substr(pos1 + 1, pos2 - pos1 - 1);
    int ind;
    if (checkrval(index, ind) && arr[arrname].assigned.count(ind)) {
        rval = arr[arrname].assigned[ind];
        return true;
    }
    else {
        return false;
    }
}

bool checklval(const string &s, int rval) {
    auto pos1 = s.find_first_of('['), pos2 = s.find_last_of(']');
    string arrname = s.substr(0, pos1);
    string index = s.substr(pos1 + 1, pos2 - pos1 - 1);
    int ind;
    if (checkrval(index, ind) && ind < arr[arrname].len) {
        arr[arrname].assigned[ind] = rval;
        return true;
    }
    else {
        return false;
    }
}

bool parseassign(const string &s, string::size_type pos) {
    string lvalstr = s.substr(0, pos), rvalstr = s.substr(pos + 1);
    int rval;
    if (checkrval(rvalstr, rval) && checklval(lvalstr, rval)) {
        return true;
    }
    else {
        return false;
    }
}

bool parse(const string &s) {
    auto pos = s.find('=');
    if (pos == string::npos) {
        parsedec(s);
        return true;
    }
    else {
        return parseassign(s, pos);
    }
}

int main() {
    string s;
    while (cin >> s && s != ".") {
        arr.clear();
        int bugline = 0, line = 1;
        if (!parse(s)) {
            printf("1\n");
            readremain();
            continue;
        }
        while (cin >> s && s != ".") {
            ++line;
            if (!parse(s)) {
                bugline = line;
                printf("%d\n", bugline);
                readremain();
                break;
            }
        }
        if (!bugline)
            printf("0\n");
    }
    return 0;
}