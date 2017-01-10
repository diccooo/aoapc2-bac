#include <cstdio>
#include <cctype>

int main()
{
	char box[5][5];
	int t = 0;
	while ((box[0][0] = getchar()) != 'Z') {
		++t;
		for (int i = 1; i < 5; ++i) {
			box[0][i] = getchar();
		}
		if (box[0][4] == '\n')
			box[0][4] = ' ';
		else
			getchar();
		for (int i = 1; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				box[i][j] = getchar();
			}
		if (box[i][4] == '\n')
			box[i][4] = ' ';
		else
			getchar();
		}
		int m, n;
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (box[i][j] == ' ') {
					m = i; n = j; break;
				}
			}
		}
		char move;
		bool flag = true;
		while ((move = getchar()) != '0') {
			if (!flag) continue;
			switch (move) {
			case 'A': 
				if (m  == 0) {
					flag = false;
					break;
				}
				box[m][n] = box[m - 1][n];
				box[m - 1][n] = ' ';
				m -= 1;
				break;
			case 'B':
				if (m == 4) {
					flag = false;
					break;
				}
				box[m][n] = box[m + 1][n];
				box[m + 1][n] = ' ';
				m += 1;
				break;
			case 'L':
				if (n == 0) {
					flag = false;
					break;
				}
				box[m][n] = box[m][n - 1];
				box[m][n - 1] = ' ';
				n -= 1;
				break;
			case 'R':
				if (n == 4) {
					flag = false;
					break;
				}
				box[m][n] = box[m][n + 1];
				box[m][n + 1] = ' ';
				n += 1;
				break;
			}
		}
		getchar();
		if (t - 1)
			printf("\n");
		printf("Puzzle #%d:\n", t);
		if (!flag)
			printf("This puzzle has no final configuration.\n");
		else {
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 5; ++j) {
					if (j != 4)
						printf("%c ", box[i][j]);
					else
						printf("%c\n", box[i][j]);
				}
			}
		}
	}
	return 0;
}