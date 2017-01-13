#include <cstdio>
#include <cstring>

int H[12][12], V[12][12];

int main() {
	int n;
	int T = 0;
	while (scanf("%d", &n) == 1) {
		memset(H, 0, sizeof(H));
		memset(V, 0, sizeof(V));
		int m;
		scanf("%d", &m);
		char s[2]; int x, y;
		while (m--) {
			scanf("%s%d%d", s, &x, &y);
			if (s[0] == 'H')
				H[x][y] = 1;
			if (s[0] == 'V')
				V[y][x] = 1;
		}
		if (T++)
			printf("\n**********************************\n\n");
		printf("Problem #%d\n\n", T);
		bool found = 0;
		for (int size = 1; size < n; ++size) {
			int num = 0;
			for (int i = 1; i <= n - size; ++i) {
				for (int j = 1; j <= n - size; ++j) {
					bool f = 1;
					for (int k = 0; k < size; ++k) {
						if (H[i][j + k] == 0 || H[i + size][j + k] == 0 || V[i + k][j] == 0 || V[i + k][j + size] == 0)
							f = 0;
					}
					if (f) ++num;
				}
			}
			if (num) {
				printf("%d square (s) of size %d\n", num, size);
				found = 1;
			}
		}
		if (!found)
			printf("No completed squares can be found.\n");
	}
	return 0;
}