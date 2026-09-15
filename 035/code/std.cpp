#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1000000;

// Sieve of Eratosthenes
bool isPrime[MAXN + 1];

void sieve() {
    fill(isPrime, isPrime + MAXN + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= MAXN; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= MAXN; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

// Check all rotations of n are prime
bool isCircular(int n) {
    if (!isPrime[n]) return false;
    string s = to_string(n);
    int len = s.size();
    for (int r = 1; r < len; r++) {
        rotate(s.begin(), s.begin() + 1, s.end());
        int rot = stoi(s);
        if (!isPrime[rot]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();

    // Precompute prefix counts
    static int pre[MAXN + 1];
    static bool done = false;
    if (!done) {
        done = true;
        pre[0] = 0;
        for (int i = 1; i <= MAXN; i++) {
            pre[i] = pre[i - 1] + (isCircular(i) ? 1 : 0);
        }
    }

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        if (N > MAXN) N = MAXN;
        // Numbers < N → count up to N-1
        if (N <= 0) cout << "0\n";
        else cout << pre[N - 1] << "\n";
    }
    return 0;
}
