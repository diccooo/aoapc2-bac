#include <cstdio>

int main() {
    long long n, sp, sq;
    while (scanf("%lld%lld%lld", &n, &sp, &sq) == 3) {
        long long k, K = ((long long)1) << 60;
        int A = 0, B = 0;
        for (int a = 0; a < 32; ++a) {
            for (int b = 0; b < 32; ++b) {
                k = (((n - 1) * sp + (((n - 1) * sp) << a)) >> b) + sq;
                if (k >= n * sq && k < K) {
                    A = a, B = b, K = k;
                }
            }
        }
        printf("%lld %d %d\n", K, A, B);
    }
    return 0;
}