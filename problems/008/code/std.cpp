#include <bits/stdc++.h>
using namespace std;

int main() {

    int T;
    cin >> T;
    while(T--) {
        int L, K;
        string S;
        cin >> L >> K >> S;

        long long ans = 0, prod = 1;
        int left = 0;
        for(int right = 0; right < L; right++) {
            int digit = S[right]-'0';
            if(digit == 0) {
                prod = 1;
                left = right+1;
                continue;
            }
            prod *= digit;

            if(right-left+1 == K) {
                ans = max(ans, prod);
                prod /= (S[left]-'0');
                left++;
            }
        }
        cout << ans << '\n';
    }
}