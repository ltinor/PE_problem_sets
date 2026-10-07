#include <bits/stdc++.h>
using namespace std;

const int MAX_STATE = 567; // 7 digits max: 7*81 = 567

int memo[MAX_STATE + 1];

int next_num(int x) {
    int sum = 0;
    while (x > 0) {
        int d = x % 10;
        sum += d * d;
        x /= 10;
    }
    return sum;
}

// returns 1 if reaches 1, 89 if reaches 89
int reach(int x) {
    if (x == 1) return 1;
    if (x == 89) return 89;
    if (memo[x] != 0) return memo[x];
    memo[x] = -1; // visiting
    int nxt = next_num(x);
    int res = reach(nxt);
    memo[x] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(memo, 0, sizeof(memo));
    memo[1] = 1;
    memo[89] = 89;

    int N;
    cin >> N;

    long long ans = 0;
    for (int i = 1; i < N; i++) {
        int nxt = next_num(i);
        if (reach(nxt) == 89) ans++;
    }

    cout << ans << "\n";
    return 0;
}
