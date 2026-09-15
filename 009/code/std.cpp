#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;

    while(T--) {
        int S;
        cin >> S;
        long long ans = 0;

        for(int n = 1; n < S/2; n++) {
            for(int m = n+1; ; m++) {
                int a = m*m - n*n;
                int b = 2*m*n;
                int c = m*m + n*n;
                int sum = a + b + c;
                if(sum > S) break;
                if(sum == S) {
                    ans = 1LL * a * b * c;
                    break;
                }
            }
            if(ans) break;
        }

        cout << ans << "\n";
    }
}