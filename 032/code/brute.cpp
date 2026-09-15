#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool is_pandigital(ll a, ll b, ll c, int n){
    vector<bool> used(n + 1, false);

    auto mark = [&](ll x){
        while(x){
            int d = x % 10;
            if(d == 0 || d > n || used[d]) return false;
            used[d] = true;
            x /= 10;
        }
        return true;
    };

    if(!mark(a)) return false;
    if(!mark(b)) return false;
    if(!mark(c)) return false;

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

    // Alternative approach: enumerate possible digit permutations
    // Generate all permutations of 1..n and split into a, b, c
    vector<int> digits(n);
    for(int i = 0; i < n; i++) digits[i] = i + 1;

    do {
        // Try all splits: a gets da digits, b gets db, c gets dc
        for(int da = 1; da <= n - 2; da++){
            ll a = 0;
            for(int i = 0; i < da; i++) a = a * 10 + digits[i];

            for(int db = 1; db <= n - da - 1; db++){
                ll b = 0;
                for(int i = da; i < da + db; i++) b = b * 10 + digits[i];

                int dc = n - da - db;
                ll c = 0;
                for(int i = da + db; i < n; i++) c = c * 10 + digits[i];

                if(a * b == c){
                    products.insert(c);
                }
            }
        }
    } while(next_permutation(digits.begin(), digits.end()));

    ll sum = 0;
    for(ll p : products) sum += p;
    cout << sum << "\n";
}
