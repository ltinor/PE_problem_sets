#include<bits/stdc++.h>
using namespace std;

const int MAXN = 10000;
int period[MAXN + 1];
int pref[MAXN + 1];

int get_period(int S) {
    int a0 = (int)sqrt(S);
    if (a0 * a0 == S) return 0;
    int m = 0, d = 1, a = a0;
    int len = 0;
    do {
        m = d * a - m;
        d = (S - m * m) / d;
        a = (a0 + m) / d;
        len++;
    } while (a != 2 * a0);
    return len;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int S = 1; S <= MAXN; S++) {
        period[S] = get_period(S);
    }
    pref[0] = 0;
    for (int i = 1; i <= MAXN; i++) {
        pref[i] = pref[i - 1] + (period[i] % 2 == 1);
    }

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        cout << pref[N] << "\n";
    }
    return 0;
}
