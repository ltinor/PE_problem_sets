#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE467 brute: generate all common superintegers for very small n
int dr(ll x) { return 1 + (x - 1) % 9; }

vector<int> gen_primes(int n) {
    vector<int> p;
    vector<bool> is_prime(1000, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; (int)p.size() < n; i++) {
        if (!is_prime[i]) continue;
        p.push_back(dr(i));
        for (int j = i + i; j < 1000; j += i) is_prime[j] = false;
    }
    return p;
}

vector<int> gen_composites(int n) {
    vector<int> c;
    vector<bool> is_prime(1000, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i < 1000; i++)
        if (is_prime[i])
            for (int j = i + i; j < 1000; j += i) is_prime[j] = false;
    for (int i = 4; (int)c.size() < n; i++)
        if (!is_prime[i]) c.push_back(dr(i));
    return c;
}

int main() {
    int n; cin >> n;
    vector<int> P = gen_primes(n);
    vector<int> C = gen_composites(n);
    
    string ps, cs;
    for (int x : P) ps += char('0'+x);
    for (int x : C) cs += char('0'+x);
    
    cout << "P_" << n << " = " << ps << "\n";
    cout << "C_" << n << " = " << cs << "\n";
}
