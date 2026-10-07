#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXP = 10000;
vector<int> primes;
bool is_p[MAXP + 1];
bool ok[1300][1300];

bool concat_prime(int a, int b) {
    string sa = to_string(a), sb = to_string(b);
    ll x = stoll(sa + sb), y = stoll(sb + sa);
    auto ip = [](ll n) {
        if (n < 2) return false;
        if (n % 2 == 0) return n == 2;
        for (ll i = 3; i * i <= n; i += 2)
            if (n % i == 0) return false;
        return true;
    };
    return ip(x) && ip(y);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int K; cin >> K;
    for (int i = 2; i <= MAXP; i++) is_p[i] = true;
    for (int i = 2; i <= MAXP; i++) {
        if (!is_p[i]) continue;
        primes.push_back(i);
        for (int j = i * i; j <= MAXP; j += i) is_p[j] = false;
    }
    int P = min((int)primes.size(), 1200);
    for (int i = 0; i < P; i++)
        for (int j = i + 1; j < P; j++)
            ok[i][j] = ok[j][i] = concat_prime(primes[i], primes[j]);

    ll best = 1e18;
    if (K == 2) {
        for (int a = 0; a < P; a++)
        for (int b = a+1; b < P; b++)
            if (ok[a][b]) best = min(best, (ll)primes[a] + primes[b]);
    }
    if (K == 3) {
        for (int a = 0; a < P; a++) { if (primes[a]*3LL >= best) break;
        for (int b = a+1; b < P; b++) { if (!ok[a][b]) continue; if (primes[a]+primes[b]*2LL >= best) break;
        for (int c = b+1; c < P; c++) { if (!ok[a][c]||!ok[b][c]) continue;
            best = min(best, (ll)primes[a]+primes[b]+primes[c]);
        }}}
    }
    if (K == 4) {
        for (int a = 0; a < P; a++) { if (primes[a]*4LL >= best) break;
        for (int b = a+1; b < P; b++) { if (!ok[a][b]) continue; if (primes[a]+primes[b]*3LL >= best) break;
        for (int c = b+1; c < P; c++) { if (!ok[a][c]||!ok[b][c]) continue; if (primes[a]+primes[b]+primes[c]*2LL >= best) break;
        for (int d = c+1; d < P; d++) { if (!ok[a][d]||!ok[b][d]||!ok[c][d]) continue;
            best = min(best, (ll)primes[a]+primes[b]+primes[c]+primes[d]);
        }}}}
    }
    if (K == 5) {
        for (int a = 0; a < P; a++) { if (primes[a]*5LL >= best) break;
        for (int b = a+1; b < P; b++) { if (!ok[a][b]) continue; if (primes[a]+primes[b]*4LL >= best) break;
        for (int c = b+1; c < P; c++) { if (!ok[a][c]||!ok[b][c]) continue; if (primes[a]+primes[b]+primes[c]*3LL >= best) break;
        for (int d = c+1; d < P; d++) { if (!ok[a][d]||!ok[b][d]||!ok[c][d]) continue; if (primes[a]+primes[b]+primes[c]+primes[d]*2LL >= best) break;
        for (int e = d+1; e < P; e++) { if (!ok[a][e]||!ok[b][e]||!ok[c][e]||!ok[d][e]) continue;
            best = min(best, (ll)primes[a]+primes[b]+primes[c]+primes[d]+primes[e]);
        }}}}}
    }
    cout << best << "\n";
}
