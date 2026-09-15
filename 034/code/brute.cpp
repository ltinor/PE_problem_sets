#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int fact[10];
    fact[0] = 1;
    for (int i = 1; i <= 9; i++) {
        fact[i] = fact[i - 1] * i;
    }

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;

        ll total = 0;
        for (int n = 3; n <= N && n <= 1000000; n++) {
            int sum = 0;
            int tmp = n;
            while (tmp > 0) {
                sum += fact[tmp % 10];
                tmp /= 10;
            }
            if (sum == n) {
                total += n;
            }
        }
        cout << total << "\n";
    }
    return 0;
}
