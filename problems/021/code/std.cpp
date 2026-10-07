#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 100000;

int div_sum[MAXN + 1];

void precompute() {
    for (int i = 1; i <= MAXN; i++) {
        for (int j = i * 2; j <= MAXN; j += i) {
            div_sum[j] += i;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    // mark amicable numbers
    vector<bool> is_amicable(MAXN + 1, false);
    for (int a = 1; a <= MAXN; a++) {
        int b = div_sum[a];
        if (b > a && b <= MAXN && div_sum[b] == a) {
            is_amicable[a] = true;
            is_amicable[b] = true;
        }
    }

    // prefix sum
    vector<ll> pref(MAXN + 1, 0);
    for (int i = 1; i <= MAXN; i++) {
        pref[i] = pref[i - 1] + (is_amicable[i] ? i : 0);
    }

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        cout << pref[N - 1] << "\n";
    }

    return 0;
}
