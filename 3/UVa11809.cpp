#include <cstdio>
#include <cmath>
#include <cstring>

int main()
{
	double M[15][35]; int E[15][35];
	for (int i = 0; i <= 9; ++i) {
		for (int j = 1; j <= 30; ++j) {
			double m = 1 - pow(2.0, -1 - i), e = pow(2.0, j) - 1;
			double t = log10(m) + e * log10(2.0);
			E[i][j] = t;
			M[i][j] = pow(10, t - E[i][j]);
		}
	}
	char s[30];
	while ((scanf("%s", &s) == 1) && strcmp(s, "0e0")) {
		char *p = strchr(s, 'e');
		*p = 0;
		double A; int B;
		sscanf(s, "%lf", &A);
		sscanf(p + 1, "%d", &B);
		while (A < 1) {
			A *= 10; B -= 1;
		}
		for (int i = 0; i <= 9; ++i) {
			for (int j = 1; j <= 30; ++j) {
				if (B == E[i][j] && (fabs(A - M[i][j]) < 1e-4 || fabs(A / 10 - M[i][j]) < 1e-4)) {
					printf("%d %d\n", i, j);
					break;
				}
			}
		}
	}
	return 0;
}