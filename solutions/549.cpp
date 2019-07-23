/**
Run 3 min on 10^8
**/
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e8;

bool memo[N + 1];
int lp[N + 1];
int binpow(int a, int n)
{
    int res = 1;
    while (n) {
        if (n & 1) {
            res = res * a;
            n--;
        }
        else {
            a = a * a;
            n >>= 1;
        }
    }
    return res;
}
int calc(int x, int y)
{
    int res = 0, cur = y;
    while (x >= cur) {
        res += x / cur;
        cur *= y;
    }
    return res;
}
int get(int x, int y)
{
    int d = sqrt(1 + 8 * x);
    int res = (d - 1) / 2;
    if (res * (res + 1) / 2 < x)
        ++res;
    res = binpow(y, res);
    while (res > y && calc(res - y, y) >= x) {
        res -= y;
    }
    return res;
}
int solve(int n)
{
    int x = n;
    int cnt = 1;
    int res = 0;
    while (x > 1) {
        if (lp[x / lp[x]] == lp[x]) {
            cnt++;
        }
        else {
            res = max(get(cnt, lp[x]), res);
            cnt = 1;
        }
        x /= lp[x];
    }
    return res;
}
main()
{
    fill(memo + 1, memo + N + 1, 1);
    memo[0] = memo[1] = false;
    for (int i = 2; i <= N; i++) {
        if (memo[i]) {
            for (int j = i; j <= N; j += i) {
                memo[j] = false;
                lp[j] = i;
            }
        }
    }
    int S = 0;
    for (int n = 2; n <= N; n++) {
        S += solve(n);
    }
    cout << S;
}

