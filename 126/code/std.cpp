#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    const int MAX_VAL = 200000;
    unordered_map<int, int> mp;

    for (int a = 1; 6LL * a * a <= MAX_VAL; a++) {
        for (int b = a; 2LL * (a*b + a*b + b*b) <= MAX_VAL; b++) {
            for (int c = b; ; c++) {
                ll base = 2LL * (a*b + b*c + c*a);
                if (base > MAX_VAL) break;
                ll sumabc = 4LL * (a + b + c);
                for (int k = 1; ; k++) {
                    ll val = base + sumabc * (k - 1) + 4LL * (k - 1) * (k - 2);
                    if (val > MAX_VAL) break;
                    mp[(int)val]++;
                }
            }
        }
    }

    int ans = MAX_VAL + 1;
    for (auto &p : mp) {
        if (p.second == K && p.first < ans)
            ans = p.first;
    }

    cout << ans << "\n";
    return 0;
}
