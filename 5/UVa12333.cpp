#include <cstdio>
#include <cstring>

using namespace std;

struct Trienode {
    Trienode *next[10];
    int i;
    Trienode() {
        i = -1;
        for (int j = 0; j < 10; ++j)
            next[j] = NULL;
    }
};

void insert(Trienode *root, int *s, int len, int i) {
    Trienode *node = root;
    for (int j = 0; j < len; ++j) {
        if(!node->next[s[j]])
            node->next[s[j]] = new Trienode;
        if(node->next[s[j]]->i == -1)
            node->next[s[j]]->i = i;
        node = node->next[s[j]];
    }
}

int query(Trienode *root, char *s) {
    Trienode *node = root;
    char *p = s;
    int a;
    while (*p) {
        a = *p - '0';
        node = node->next[a];
        ++p;
        if (node == NULL) return -1;
    }
    return node->i;
}

int fib[2][30000], f[45];

void calcfib(Trienode *trie) {
    memset(fib, 0, sizeof(fib));
    fib[0][0] = fib[1][0] = 1;
    f[0] = 1;
    insert(trie, f, 1, 0);
    int p, q;
    int s = 0, l = 1;
    for (int i = 2; i < 100000; ++i) {
        p = i % 2; q = (i + 1) % 2;
        for (int j = s; j < l; ++j)
            fib[p][j] += fib[q][j];
        for (int j = s; j < l; ++j) {
            if (fib[p][j] >= 10) {
                fib[p][j] -= 10;
                fib[p][j + 1] += 1;
            }
        }
        if (fib[p][l]) ++l;
        if (l - s > 50) ++s;
        int len = 0;
        for (int j = l - 1; j >= 0; --j) {
            f[len++] = fib[p][j];
            if (len > 40) break;
        }
        insert(trie, f, len, i);
    }
}

int main() {
    Trienode *trie = new Trienode;
    calcfib(trie);
    int T;
    scanf("%d", &T);
    char s[45];
    for (int k = 1; k <= T; ++k) {
        scanf("%s", s);
        printf("Case #%d: %d\n", k, query(trie, s));
    }
    return 0;
}