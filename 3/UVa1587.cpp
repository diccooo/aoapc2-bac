#include <cstdio>

bool isbox(int a[6][2]) {
	for (int i = 0; i < 3; ++i) {
		if (a[2 * i][0] != a[2 * i + 1][0] || a[2 * i][1] != a[2 * i + 1][1])
			return false;
	}
	if (a[0][0] != a[2][0] || a[0][1] != a[4][0] || a[2][1] != a[4][1])
		return false;
	return true;
}

int main()
{
	int a[6][2];
	while (scanf("%d%d", &a[0][0], &a[0][1]) == 2) {
		for (int i = 1; i < 6; ++i) {
			scanf("%d%d", &a[i][0], &a[i][1]);
		}
		for (int i = 0; i < 6; ++i) {
			if (a[i][0] < a[i][1]) {
				int temp = a[i][0];
				a[i][0] = a[i][1];
				a[i][1] = temp;
			}
		}
		for (int i = 1; i < 6; ++i) {
			int j = i;
			while (j) {
				if (a[j][0] > a[j - 1][0]) {
					int temp[2];
					temp[0] = a[j][0]; temp[1] = a[j][1];
					a[j][0] = a[j - 1][0]; a[j][1] = a[j - 1][1];
					a[j - 1][0] = temp[0]; a[j - 1][1] = temp[1];
				}
				if (a[j][0] == a[j - 1][0] && a[j][1] > a[j - 1][1]) {
					int temp[2];
					temp[0] = a[j][0]; temp[1] = a[j][1];
					a[j][0] = a[j - 1][0]; a[j][1] = a[j - 1][1];
					a[j - 1][0] = temp[0]; a[j - 1][1] = temp[1];
				}
				--j;
			}
		}
		if (isbox(a))
			printf("POSSIBLE\n");
		else
			printf("IMPOSSIBLE\n");
	}
	return 0;
}