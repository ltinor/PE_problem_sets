#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 259: Sum of all reachable numbers using digits 1-9 in order
// Can concatenate adjacent digits, use + - * /, parentheses allowed
// No unary minus. Goal: sum all positive integers reachable.

// Use recursive enumeration of all expressions
// A number is reachable if there exists an expression using 1..9
// We evaluate all possible expressions and collect reachable ints.

set<ll> reachable;

// Evaluate expression from start to end (exclusive) of digit string
// Returns set of all possible values
set<ll> eval_range(int l, int r) {
    // digits[l..r) form a sub-expression
    // We can either use the concatenated number, or split at k
    // with an operator
    set<ll> res;
    // Option: just the concatenated number
    ll num = 0;
    for (int i = l; i < r; i++) num = num*10 + (i+1);
    res.insert(num);
    // Try all split points and operators
    for (int k = l+1; k < r; k++) {
        auto left = eval_range(l, k);
        auto right = eval_range(k, r);
        for (ll a : left) for (ll b : right) {
            res.insert(a + b);
            res.insert(a - b);
            res.insert(a * b);
            if (b != 0 && a % b == 0) res.insert(a / b);
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    cin >> n;
    
    // DP: for each subrange [l,r) of digits 1..n, compute set of reachable values
    map<pair<int,int>, set<ll>> memo;
    function<set<ll>(int,int)> dfs = [&](int l, int r) -> set<ll> {
        if (memo.count({l,r})) return memo[{l,r}];
        set<ll> res;
        ll num = 0;
        for (int i = l; i < r; i++) num = num*10 + (i+1);
        res.insert(num);
        for (int k = l+1; k < r; k++) {
            auto L = dfs(l, k), R = dfs(k, r);
            for (ll a : L) for (ll b : R) {
                res.insert(a + b);
                res.insert(a - b);
                res.insert(a * b);
                if (b != 0 && a % b == 0) res.insert(a / b);
            }
        }
        return memo[{l,r}] = res;
    };
    
    auto all = dfs(0, n);
    ll sum = 0;
    for (ll x : all) if (x > 0) sum += x;
    cout << sum << "\n";
}
