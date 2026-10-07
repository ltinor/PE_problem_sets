#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000000;
int fact[10];

int digit_fact_sum(int x) {
    if (x == 0) return fact[0];
    int s = 0;
    while (x) {
        s += fact[x % 10];
        x /= 10;
    }
    return s;
}

int chain_length(int start) {
    unordered_map<int, int> seen;
    int cur = start;
    int step = 0;
    while (!seen.count(cur)) {
        seen[cur] = step++;
        cur = digit_fact_sum(cur);
    }
    return step;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fact[0] = 1;
    for (int i = 1; i <= 9; i++) fact[i] = fact[i-1] * i;

    int N, K;
    cin >> N >> K;

    int ans = 0;
    for (int i = 1; i < N; i++) {
        if (chain_length(i) == K) ans++;
    }

    cout << ans << "\n";
    return 0;
}
