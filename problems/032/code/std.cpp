#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool is_pandigital(ll a, ll b, ll c, int n){
    vector<bool> used(n + 1, false);

    auto check = [&](ll x){
        while(x){
            int d = x % 10;
            if(d == 0 || d > n || used[d]) return false;
            used[d] = true;
            x /= 10;
        }
        return true;
    };

    if(!check(a)) return false;
    if(!check(b)) return false;
    if(!check(c)) return false;

    for(int i = 1; i <= n; i++){
        if(!used[i]) return false;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    set<ll> products;
    int max_digits_a, max_digits_b;

    // Total digits in a,b,c together must equal n
    // c = a * b, so digits(c) ≈ digits(a) + digits(b) or digits(a)+digits(b)-1
    // We need digits(a) + digits(b) + digits(c) = n
    // So digits(a) + digits(b) <= n - 1 (c has at least 1 digit)
    // And digits(c) = n - digits(a) - digits(b)
    // Also digits(c) ∈ [digits(a)+digits(b)-1, digits(a)+digits(b)]

    for(int da = 1; da <= n - 2; da++){
        ll min_a = 1;
        for(int i = 1; i < da; i++) min_a *= 10;
        ll max_a = min_a * 10 - 1;

        for(int db = 1; db <= n - da - 1; db++){
            ll min_b = 1;
            for(int i = 1; i < db; i++) min_b *= 10;
            ll max_b = min_b * 10 - 1;

            int dc = n - da - db;
            ll min_c = 1;
            for(int i = 1; i < dc; i++) min_c *= 10;
            ll max_c = min_c * 10 - 1;

            for(ll a = min_a; a <= max_a; a++){
                for(ll b = min_b; b <= max_b; b++){
                    ll c = a * b;
                    if(c < min_c || c > max_c) continue;
                    if(is_pandigital(a, b, c, n)){
                        products.insert(c);
                    }
                }
            }
        }
    }

    ll sum = 0;
    for(ll p : products) sum += p;
    cout << sum << "\n";
}
