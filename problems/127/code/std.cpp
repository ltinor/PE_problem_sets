#include<bits/stdc++.h>
using namespace std;
#define ll long long

int mygcd(int a, int b) { while(b){int t=b; b=a%b; a=t;} return a; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    vector<ll> rad(M + 1, 1);
    for (int i = 2; i <= M; i++) {
        if (rad[i] == 1) {
            for (int j = i; j <= M; j += i)
                rad[j] *= i;
        }
    }

    ll ans = 0;
    for (int a = 1; a < M; a++) {
        for (int b = a + 1; a + b < M; b++) {
            int c = a + b;
            if (mygcd(a, b) != 1) continue;
            if (rad[a] * rad[b] * rad[c] < c)
                ans += c;
        }
    }

    cout << ans << "\n";
    return 0;
}
