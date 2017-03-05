#include <cstdio>
#include <stack>
#include <vector>

using namespace std;

struct Card {
    char value, suit;
};

stack<Card> cards[52];

int match(int i) {
    int res = -1, n = 0, t = i - 1;
    if (!cards[i].empty()) {
        while (t >= 0 && n <= 3) {
            if (cards[t].empty()) {
                --t; continue;
            }
            ++n;
            if (n == 1 || n == 3) {
                if (cards[t].top().value == cards[i].top().value || cards[t].top().suit == cards[i].top().suit) {
                    res = t;
                }
            }
            --t;
        }
    }
    return res;
}

bool move() {
    for (int i = 0; i < 52; ++i) {
        int m = match(i);
        if (m != -1) {
            cards[m].push(cards[i].top());
            cards[i].pop();
            return true;
        }
    }
    return false;
}

int main() {
    char s[5];
    Card tmp;
    while (scanf("%s", s) == 1 && s[0] != '#') {
        cards[0] = stack<Card>();
        tmp.value = s[0]; tmp.suit = s[1];
        cards[0].push(tmp);
        for (int i = 1; i < 52; ++i) {
            scanf("%s", s);
            cards[i] = stack<Card>();
            tmp.value = s[0]; tmp.suit = s[1];
            cards[i].push(tmp);
        }
        for (;;) {
            if (!move()) break;
        }
        int n = 0;
        vector<int> piles;
        for (int i = 0; i < 52; ++i) {
            if (!cards[i].empty()) {
                ++n;
                piles.push_back(cards[i].size());
            }
        }
        printf("%d pile", n);
        if (n > 1) printf("s");
        printf(" remaining:");
        for (auto it = piles.begin(); it != piles.end(); ++it) {
            printf(" %d", *it);
        }
        printf("\n");
    }
    return 0;
}