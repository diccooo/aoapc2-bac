#include <cstdio>
#include <cstring>

char master[105], driven[105];

int main()
{
	while (scanf("%s%s", master, driven) == 2) {
		int min1, min2;
		char *s = master, *p = s, *q = driven;
		while (*p && *q) {
			if (*p != '2' || *q != '2') {
				++p; ++q;
			}
			else {
				++s;
				p = s; q = driven;
			}
		}
		min1 = strlen(master) + strlen(driven) - (q - driven);
		s = driven, p = s, q = master;
		while (*p && *q) {
			if (*p != '2' || *q != '2') {
				++p; ++q;
			}
			else {
				++s;
				p = s; q = master;
			}
		}
		min2 = strlen(master) + strlen(driven) - (q - master);
		printf("%d\n", (min1 < min2 ? min1 : min2));
	}
	return 0;
}