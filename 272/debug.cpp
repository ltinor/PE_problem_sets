#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Debug: compute sum for specific A
ll sum_neutral(ll X, ll A, const vector<ll>& neutral) {
    ll sum = 0;
    for (ll m : neutral) {
        if (m > X) break;
        if (gcd(m, A) == 1) sum += m;
    }
    return sum;
}

int main() {
    // Generate neutral numbers up to 100
    vector<ll> np;
    np.push_back(3);
    for (ll p = 2; p <= 100; p++) {
        if (p % 3 == 2) {
            bool isp = true;
            for (ll d = 2; d*d <= p; d++) if(p%d==0){isp=false;break;}
            if (isp) np.push_back(p);
        }
    }
    
    set<ll> nums;
    function<void(int,ll)> dfs = [&](int idx, ll cur) {
        nums.insert(cur);
        if (idx >= (int)np.size()) return;
        ll p = np[idx];
        dfs(idx+1, cur);
        int max_e = (p==3)?1:60;
        ll pp = p;
        for (int e=1; e<=max_e && cur <= 100/pp; e++) {
            dfs(idx+1, cur*pp);
            if (pp > 100/p) break; pp *= p;
        }
    };
    dfs(0,1);
    
    vector<ll> neutral(nums.begin(), nums.end());
    sort(neutral.begin(), neutral.end());
    
    cout << "Neutral numbers up to 100:\n";
    for (ll m : neutral) cout << m << " ";
    cout << "\n\n";
    
    // For T=1 active primes: 7, 9, 13, 19, 27, 31, 37, 43, 49, 61, 67, 73, 79, 81, 97
    vector<ll> active = {7,9,13,19,27,31,37,43,49,61,67,73,79,81,97};
    ll N = 100;
    ll total = 0;
    for (ll A : active) {
        ll maxM = N / A;
        ll s = sum_neutral(maxM, A, neutral);
        ll contrib = A * s;
        total += contrib;
        cout << "A=" << A << " maxM=" << maxM << " sumM=" << s << " contrib=" << contrib << "\n";
    }
    cout << "\nTotal: " << total << "\n";
}
