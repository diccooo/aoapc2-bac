#include <cstdio>
#include <algorithm>
#include <cstring>

char table[150][10];
struct Cont {
	char context[12];
	char concode[80];
	bool operator < (const Cont a) const {
        return strcmp(context,a.context) < 0;
    }
} cont[105];

bool match(char *s1, char *s2, int &d) {
	int len1 = strlen(s1), len2 = strlen(s2), len;
	if (len1 < len2) {
		len = len1;
	}
	else {
		len = len2;
	}
	for (int i = 0; i < len; ++i) {
		if (s1[i] != s2[i]) {
			return false;
		}
	}
	d = len1 > len2 ? (len1 - len2) : (len2 - len1);
	return true;
}

int main() {
	memset(table, 0, sizeof(table));
	char C[2];
	while(scanf("%s", C) == 1 && C[0] != '*') {
		scanf("%s", table[C[0]]);
	}
	int n = 0;
	while (scanf("%s", cont[n].context) == 1 && cont[n].context[0] != '*') {
		int len = strlen(cont[n].context);
		int m = 0;
		for (int i = 0; i < len; ++i) {
			int l = strlen(table[cont[n].context[i]]);
			for (int j = 0; j < l; ++j) {
				cont[n].concode[m++] = table[cont[n].context[i]][j];
			}
		}
		++n;
	}
	std::sort(cont, cont + n);
	char code[100];
	while (scanf("%s", code) == 1 && code[0] != '*') {
		int md = 1000, t, emarkn = 0;
		for (int i = 0; i < n; ++i) {
			int d = md;
			if (match(code, cont[i].concode, d)) {
				if (d < md) {
					md = d;
					t = i;
				}
				if (d == 0) ++emarkn;
			}
		}
		if (md == 1000) t = 0;
		printf("%s", cont[t].context);
		if (emarkn > 1) printf("!");
		if (md) printf("?");
		printf("\n");
	}
	return 0;
}