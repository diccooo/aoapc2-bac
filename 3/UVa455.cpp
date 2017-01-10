#include <cstdio>
#include <cstring>

bool isperiodm(char* s, int m);

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		char s[85];
		scanf("%s", s);
		int sl = strlen(s);
		int p;
		for (p = 1; p <= sl; ++p) {
			if (isperiodm(s, p)) {
				if (T != 0) {
					printf("%d\n\n", p);
					break;
				}
				else {
					printf("%d\n", p);
					break;
				}
			}
		}
	}
	return 0;
}

bool isperiodm(char* s, int m)
{
	int sl = strlen(s);
	if (sl % m != 0)
		return false;
	int n = sl / m;
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (s[i * m + j] != s[j])
				return false;
		}
	}
	return true;
}