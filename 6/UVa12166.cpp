/* http://blog.csdn.net/kun768/article/details/43208669
 *
 *Ҫ��ʹ����������ƽ�⣬�����Ϊd����Ϊw�ĳ���Ϊ��׼�������һ������������������w*pow(2,d) �� w<<d
 *�����н��ֵ��Ӧ������������������������������ظ��������ļ�Ҫ����������Ϊƽ��ı�׼��
 *��ô������Щ����ѭ��׼�Ľ��ֵ���ı伴Ϊ���ټ����ܽ����� - �������ظ��������
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