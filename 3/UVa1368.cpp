#include <cstdio>
#include <cstring>

char seq[55][1010];
char constr[1010];
const char acgt[4] = {'A', 'C', 'G', 'T'};

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, l;
		scanf("%d%d", &n, &l);
		memset(seq, 0, sizeof(seq));
		memset(constr, 0, sizeof(constr));
		for (int i = 0; i < n; ++i) {
			scanf("%s", seq[i]);
		}
		for (int i = 0; i < l; ++i) {
			int num[4] = {0, 0, 0, 0};
			for (int j = 0; j < n; ++j) {
				switch (seq[j][i]) {
				case 'A': num[0] += 1; break;
				case 'C': num[1] += 1; break;
				case 'G': num[2] += 1; break;
				case 'T': num[3] += 1; break;
				}
			}
			int max = 0;
			for (int j = 1; j < 4; ++j) {
				if (num[j] > num[max])
					max = j;
			}
			constr[i] = acgt[max];
			printf("%c", constr[i]);
		}
		printf("\n");
		int dist = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < l; ++j) {
				if (seq[i][j] != constr[j])
					++dist;
			}
		}
		printf("%d\n", dist);
	}
	return 0;
}