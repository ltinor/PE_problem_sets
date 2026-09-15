#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

i128 gcd128(i128 a, i128 b) {
    while (b) { a %= b; swap(a, b); }
    return a;
}

int main() {
    ll p = 3;
    i128 num = 0, den = 1;
    ll last_not_div = -1;
    bool was_div = false;
    
    for (ll n = 1; n <= 200; n++) {
        i128 new_num = num * n + den;
        i128 new_den = den * n;
        i128 g = gcd128(new_num, new_den);
        num = new_num / g;
        den = new_den / g;
        
        bool curr_div = (den % p == 0);
        if (!curr_div) last_not_div = n;
        
        if (curr_div != was_div) {
            cout << "n=" << n << ": den=" << (ll)den << " div_by_" << p << "=" << curr_div;
            if (!curr_div) cout << " (recovered)";
            cout << endl;
            was_div = curr_div;
        }
    }
    cout << "Last not div by " << p << ": " << last_not_div << endl;
    return 0;
}
