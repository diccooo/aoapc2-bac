/* http://blog.csdn.net/kun768/article/details/43208669
 *
 *要想使整个二叉树平衡，以深度为d重量为w的秤砣为基准可以算出一个二叉树的总重量：w*pow(2,d) 即 w<<d
 *将所有结点值对应的总重量都算出来，看出现总重量重复次数最多的即要将此重量作为平衡的标准，
 *那么，将那些不遵循标准的结点值都改变即为最少即：总结点个数 - 总重量重复次数最多
 *
 */

#include <cstdio>
#include <map>
#include <cctype>

using namespace std;

int cur = 0;
char str[1 << 19];
map<long long, int> cnt;

void dfs(int dep) {
    if (isdigit(str[cur])) {
        long long a = 0;
        while (isdigit(str[cur]))
            a = a * 10 + str[cur++] - '0';
        cnt[a << dep]++;
    }
    else {
        cur++;          // [
        dfs(dep + 1);
        cur++;          // ,
        dfs(dep + 1);
        cur++;          // ]
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        cur = 0; cnt.clear();
        scanf("%s", str);
        dfs(0);
        int mx = 0, sum = 0;
        for (auto it = cnt.begin(); it != cnt.end(); ++it) {
            sum += it->second;
            if (mx < it->second)
                mx = it->second;
        }
        printf("%d\n", sum - mx);
    }
    return 0;
}