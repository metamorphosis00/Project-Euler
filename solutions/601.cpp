#include <stdio.h>
#define int long long

using namespace std;

int gcd(int x, int y)
{
    return (y == 0) ? x : gcd(y, x % y);
}
int lcm(int x, int y)
{
    return x / gcd(x, y) * y;
}
int calc(int k, int N)
{
    N -= 2;
    int l = 1;
    for (int i = 2; i <= k; i++)
        l = lcm(l, i);
    return N / l - N / lcm(l, k + 1);
}
main()
{
    int ans = 0;
    for (int i = 1; i <= 31; i++)
        ans += calc(i, (1ll << (2 * i)));
    printf("%I64d\n", ans);
}
