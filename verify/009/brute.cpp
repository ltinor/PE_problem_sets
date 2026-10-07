#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while(T--) {
        int S;
        cin >> S;
        long long ans = 0;

        for(int a = 1; a < S/3; a++) {
            for(int b = a+1; b < S/2; b++) {
                int c = S - a - b;
                if(c <= b) continue;
                if(1LL*a*a + 1LL*b*b == 1LL*c*c) {
                    ans = 1LL*a*b*c;
                    break;
                }
            }
            if(ans) break;
        }

        cout << ans << "\n";
    }
}