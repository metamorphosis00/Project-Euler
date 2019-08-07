#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N   = 1e5;
const int M   = 1000 * 1000 * 1000 * 1000ll;
const int MOD = (1ll << 32);

namespace number {

    bool isPrime(int n)
    {
        if (n < 2) return false;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

    int phi(int n)
    {
        int res = n;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                while (n % i == 0) {
                    n /= i;
                }
                res -= res / i;
            }
        }
        if (n > 1) {
            res -= res / n;
        }
        return res;
    }
};

vector<int> primes;
vector<int> hammings;
void getHammings()
{
    for (int two = 1; two <= M; two *= 2) {
        for (int three = 1; three * two <= M; three *= 3) {
            for (int five = 1; two * three * five <= M; five *= 5) {
                if (two * three * five > 1) {
                    hammings.push_back(two * three * five);
                }
            }
        }
    }
    sort(hammings.begin(), hammings.end());
}
void getPrimes()
{
    assert(!hammings.empty());
    for (int hamming : hammings) {
        if (hamming > 5 && number::isPrime(hamming + 1)) {
            primes.push_back(hamming + 1);
        }
    }
}
void init()
{
    getHammings();
    getPrimes();
}
int solveNaive()
{
    int res = 0;
    for (int i = 1; i <= M; i++) {
        int p = number::phi(i);
        while (p % 5 == 0) p /= 5;
        while (p % 3 == 0) p /= 3;
        while (p % 2 == 0) p /= 2;
        if (p == 1) {
            res += i;
        }
    }
    return res;
}
int add(int x, int y)
{
    return (x % MOD + y % MOD) % MOD;
}
int calc(int cur = 0, int p = 1)
{
    if (p > M / primes[cur] || cur >= (int)primes.size()) {
        int res = p;
        if (p > 1) {
            for (int hamming : hammings) {
                if (hamming > M / p) {
                    break;
                }
                res = add(res, hamming * p);
            }
        }
        return res;
    }
    return add(calc(cur + 1, p * primes[cur]), calc(cur + 1, p));
}
int solve()
{
    init();
    return add(calc(), accumulate(hammings.begin(), hammings.end(), 0, add));
}
main() {
    cout << solve();
}

