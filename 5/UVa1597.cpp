#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

const int maxl = 1500 + 10;
const int maxn = 100 + 5;
const string mless[] = {"the", "a", "to", "and", "or", "not"};

struct Doc {
    int lnum;
    string lines[maxl];
} doc[maxn];

map<string, map<int, set<int>>> vocab;

void tokenize(string &s, int dnum, int lnum) {
    for (auto i = s.begin(); i != s.end(); ++i) {
        if (!isalpha(*i))
            *i = ' ';
        if (isupper(*i))
            (*i) += 32;
    }
    stringstream ss(s);
    string word;
    while (ss >> word) {
        bool f = 0;
        for (int i = 0; i < 6; ++i) {
            if (word == mless[i]) {
                f = 1; break;
            }
        }
        if (f) continue;
        if (!vocab.count(word)) {
            vocab[word] = map<int, set<int>>();
        }
        if (!vocab[word].count(dnum)) {
            vocab[word][dnum] = set<int>();
        }
        if (!vocab[word][dnum].count(lnum)) {
            vocab[word][dnum].insert(lnum);
        }
    }
}

bool qnot(const string &s, const int n) {
    bool f = 0;
    int t = 0;
    auto m = vocab.count(s);
    for (int i = 0; i < n; ++i) {
        if (!m || !vocab[s].count(i)) {
            f = 1;
            if (t++) {
                cout << "----------\n";
            }
            for (int j = 0; j < doc[i].lnum; ++j) {
                cout << doc[i].lines[j] << endl;
            }
        }
    }
    if (f) {
        cout << "==========\n";
    }
    return f;
}

void qprint(map<int, set<int>> &did) {
    int t = 0;
    for (auto i = did.begin(); i != did.end(); ++i) {
        if (t++) {
            cout << "----------\n";
        }
        for (auto j = i->second.begin(); j != i->second.end(); ++j) {
            cout << doc[i->first].lines[*j] << endl;
        }
    }
    cout << "==========\n";
}

bool qandor(const string &boolop, const string &s1, const string &s2, int n) {
    map<int, set<int>> did;
    if (boolop == "and") {
        if (!vocab.count(s1) || !vocab.count(s2))
            return false;
        set<int> dnum;
        for (int i = 0; i < n; ++i) {
            if (vocab[s1].count(i) && vocab[s2].count(i)) {
                dnum.insert(i);
            }
        }
        for (auto i = dnum.begin(); i != dnum.end(); ++i) {
            did[*i] = set<int>();
            set_union(vocab[s1][*i].begin(), vocab[s1][*i].end(), vocab[s2][*i].begin(), vocab[s2][*i].end(), inserter(did[*i], did[*i].begin()));
        }
    }
    if (boolop == "or") {
        if (!vocab.count(s1) && !vocab.count(s2))
            return false;
        else if (!vocab.count(s1))
            did = vocab[s2];
        else if (!vocab.count(s2))
            did = vocab[s1];
        else {
            did = vocab[s1];
            for (auto i = vocab[s2].begin(); i != vocab[s2].end(); ++i) {
                if (did.count(i->first)) {
                    for (auto j = i->second.begin(); j != i->second.end(); ++j) {
                        did[i->first].insert(*j);
                    }
                }
                else {
                    did[i->first] = i->second;
                }
            }
        }
    }
    if (did.empty()) {
        return false;
    }
    else {
        qprint(did);
        return true;
    }
}

bool qsingle(const string &s) {
    if (!vocab.count(s)) {
        return false;
    }
    else {
        qprint(vocab[s]);
        return true;
    }
}

void query(string &s, int n) {
    for (auto i = s.begin(); i != s.end(); ++i) {
        if (isupper(*i))
            (*i) += 32;
    }
    stringstream ss(s);
    string qstr[3];
    int i = 0;
    while (ss >> qstr[i]) ++i;
    bool f;
    if (qstr[0] == "not") {
        f = qnot(qstr[1], n);
    }
    else if (qstr[1] != "") {
        f = qandor(qstr[1], qstr[0], qstr[2], n);
    }
    else {
        f = qsingle(qstr[0]);
    }
    if (!f) {
        cout << "Sorry, I found nothing.\n==========\n";
    }
}

int main() {
    string tmp;
    int N;
    getline(cin, tmp);
    stringstream sstmp(tmp);
    sstmp >> N;
    for (int i = 0; i < N; ++i) {
        int lnum = 0;
        string s;
        while (getline(cin, s) && s != "**********") {
            doc[i].lines[lnum] = s;
            tokenize(s, i, lnum);
            ++lnum;
        }
        doc[i].lnum = lnum;
    }
    int M;
    getline(cin, tmp);
    stringstream sstmp1(tmp);
    sstmp1 >> M;
    for (int i = 0; i < M; ++i) {
        string s;
        getline(cin, s);
        query(s, N);
    }
    return 0;
}