#include <bits/stdc++.h>
using namespace std;

int main() {


    int T;
    cin >> T;

    while(T--) {
        int L, K;
        string S;
        cin >> L >> K >> S;

        long long ans = 0;

        for(int i = 0; i + K <= L; i++) {
            long long prod = 1;
            for(int j = 0; j < K; j++) {
                int digit = S[i+j] - '0';
                prod *= digit;
            }
            ans = max(ans, prod);
        }

        cout << ans << "\n";
    }
}