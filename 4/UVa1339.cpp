#include <cstdio>
#include <cstring>
#include <algorithm>

int main()
{
	char s1[105], s2[105];
	while (scanf("%s%s", s1, s2) == 2) {
		int n = strlen(s1);
		int cnt1[26] = {0}, cnt2[26] = {0};
		for (int i = 0; i < n; ++i)
			++cnt1[s1[i] - 'A'];
		for (int i = 0; i < n; ++i)
			++cnt2[s2[i] - 'A'];
		std::sort(cnt1, cnt1 + 26);
		std::sort(cnt2, cnt2 + 26);
		bool f = true;
		for (int i = 0; i < 26; ++i) {
			if (cnt1[i] != cnt2[i])
				f = false;
		}
		if (f)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}