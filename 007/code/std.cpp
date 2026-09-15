#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    
    // Find max K from input
    vector<int> queries(T);
    int maxK = 0;
    for (int i = 0; i < T; i++) {
        cin >> queries[i];
        maxK = max(maxK, queries[i]);
    }
    
    // nth prime bound: p_n < n*(log n + log log n) for n>=6
    double x = maxK;
    int N = max(100, (int)(x * (log(x) + log(log(x))) + 10));
    
    vector<char> is_prime(N + 1, 1);
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i * i <= N; i++) {
        if (is_prime[i])
            for (int j = i * i; j <= N; j += i)
                is_prime[j] = 0;
    }
    
    vector<int> primes;
    primes.reserve(maxK);
    for (int i = 2; i <= N && (int)primes.size() < maxK; i++)
        if (is_prime[i]) primes.push_back(i);
    
    for (int k : queries)
        cout << primes[k - 1] << "\n";
}
