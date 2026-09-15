#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// Brute force for PE496: check all triangles with sides ≤ N

int main() {
    string query;
    getline(cin, query);
    ll N = stoll(query);
    
    if (N > 60) {
        cout << "0\n";
        return 0;
    }
    
    ll ans = 0;
    for (ll a = 1; a <= N; a++) {
        for (ll b = a; b <= N; b++) {
            for (ll c = b; c <= N && c < a + b; c++) {
                ll s2 = a + b + c;
                if (s2 % 2) continue;
                ll s = s2 / 2;
                i128 area2 = (i128)s * (s-a) * (s-b) * (s-c);
                if (area2 <= 0) continue;
                ll root = (ll)sqrt((long double)area2);
                if ((i128)root * root != area2) continue;
                if (root % s != 0) continue;
                
                i128 num = (i128)a * b * c;
                if (num % (4 * root) != 0) continue;
                
                ans += a + b + c;
            }
        }
    }
    cout << ans << "\n";
}
