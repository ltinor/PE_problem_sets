#include<bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

long long lcm(long long a, long long b) {
    return a / gcd(a,b) * b;
}

int main() {
    int T;
    cin >> T;

    while(T--) {
        int n;
        cin >> n;

        long long ans = 1;
        for(int i = 1; i <= n; i++) {
            ans = lcm(ans, i);
        }

        cout << ans << endl;
    }
}