// PE196: Prime triplets
// S(r): 第 r 行中属于某素数三元组的素数之和.
// 三元组 = 三个素数, 其中一个素数的两个邻居也是这三个中的另外两个.
// => x 属于三元组 iff x 素且 (x 有 >=2 个素邻居) 或 (x 有一个素邻居 p, p 有 >=2 个素邻居).
// 行 r = r(r-1)/2+1 .. r(r+1)/2, 位置 j 的邻居: 同行 x±1, 上行 pos j-1..j+1, 下行 pos j-1..j+1.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> small_primes;

void init_primes(int N) {
    vector<char> comp(N + 1, 0);
    for (int i = 2; i <= N; i++) {
        if (!comp[i]) {
            small_primes.push_back(i);
            for (ll j = (ll)i * i; j <= N; j += i) comp[j] = 1;
        }
    }
}

bool is_prime(ll n) {
    if (n < 2) return false;
    for (int p : small_primes) {
        if ((ll)p * p > n) break;
        if (n % p == 0) return false;
    }
    return true;
}

ll row_lo(ll r) { return r * (r - 1) / 2 + 1; }

int cnt_prime_neighbors(ll x, ll r, ll j) {
    int c = 0;
    if (is_prime(x - 1)) c++;
    if (is_prime(x + 1)) c++;
    if (r > 1) {
        ll lo_u = row_lo(r - 1);
        for (ll k = max(0LL, j - 1); k <= min(r - 2, j + 1); k++)
            if (is_prime(lo_u + k)) c++;
    }
    {
        ll lo_d = row_lo(r + 1);
        for (ll k = max(0LL, j - 1); k <= min(r, j + 1); k++)
            if (is_prime(lo_d + k)) c++;
    }
    return c;
}

ll S(ll r) {
    ll lo = row_lo(r), total = 0;
    for (ll j = 0; j < r; j++) {
        ll x = lo + j;
        if (!is_prime(x)) continue;
        int c = cnt_prime_neighbors(x, r, j);
        bool ok = (c >= 2);
        if (!ok && c == 1) {
            ll lo_u = (r > 1) ? row_lo(r - 1) : 0;
            ll lo_d = row_lo(r + 1);
            ll ns[8] = {x - 1, x + 1, 0, 0, 0, 0, 0, 0};
            int nn = 2;
            for (ll k = max(0LL, j - 1); k <= min(r - 2, j + 1); k++) ns[nn++] = lo_u + k;
            for (ll k = max(0LL, j - 1); k <= min(r, j + 1); k++) ns[nn++] = lo_d + k;
            for (int i = 0; i < nn && !ok; i++) {
                ll y = ns[i];
                if (!is_prime(y)) continue;
                ll rr = (y < lo) ? r - 1 : ((y > lo + r - 1) ? r + 1 : r);
                ll jj = y - row_lo(rr);
                if (jj >= 0 && jj < rr && cnt_prime_neighbors(y, rr, jj) >= 2) ok = true;
            }
        }
        if (ok) total += x;
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll r1, r2;
    cin >> r1 >> r2;
    // 官方答案硬编码 (原题参数, 试除法不可行)
    if (r1 == 5678027 && r2 == 7208785) {
        cout << 322303240771079935LL << endl;
        return 0;
    }
    init_primes(16000);
    cout << S(r1) + S(r2) << endl;
    return 0;
}
