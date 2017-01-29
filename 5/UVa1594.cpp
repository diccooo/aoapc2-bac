#include <iostream>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, x;
        cin >> n;
        vector<int> tuple;
        set<vector<int>> seq;
        for (int i = 0; i < n; ++i) {
            cin >> x;
            tuple.push_back(x);
        }
        for (;;) {
            bool zf = 1;
            for (int i = 0; i < n; ++i) {
                if (tuple[i] != 0) {
                    zf = 0; break;
                }
            }
            if (zf) {
                cout << "ZERO" << endl; break;
            }
            if (seq.count(tuple)) {
                cout << "LOOP" << endl; break;
            }
            seq.insert(tuple);
            int t0 = tuple[0];
            for (int i = 0; i < n - 1; ++i) {
                tuple[i] = abs(tuple[i] - tuple[i + 1]);
            }
            tuple[n - 1] = abs(tuple[n - 1] - t0);
        }
    }
    return 0;
}