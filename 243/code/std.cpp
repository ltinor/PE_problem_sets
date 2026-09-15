#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// Find smallest d such that φ(d)/(d-1) < A/B
// Strategy: try d that are products of consecutive primes (starting from 2)
// then multiply by small primes to reduce the ratio further

vector<int> primes;
bool is_prime_arr[100000];

void sieve(int limit) {
    fill(is_prime_arr, is_prime_arr + limit + 1, true);
    is_prime_arr[0] = is_prime_arr[1] = false;
    for (int i = 2; i <= limit; i++) {
        if (is_prime_arr[i]) {
            primes.push_back(i);
            for (ll j = (ll)i * i; j <= limit; j += i)
                is_prime_arr[j] = false;
        }
    }
}

// Compute φ(d)/d = ∏(1-1/p) for given prime exponents
long double phi_ratio(ll d) {
    long double r = 1.0;
    ll tmp = d;
    for (int p : primes) {
        if ((ll)p * p > tmp) break;
        if (tmp % p == 0) {
            r *= (long double)(p - 1) / p;
            while (tmp % p == 0) tmp /= p;
        }
    }
    if (tmp > 1) r *= (long double)(tmp - 1) / tmp;
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll A, B;
    cin >> A >> B;
    
    long double target = (long double)A / B;
    
    sieve(1000);
    
    // Strategy: build d as product of first k primes, then keep multiplying by the
    // smallest prime factor until the ratio drops below target
    // We need R(d) = φ(d)/(d-1) < A/B
    
    // Try different numbers of initial primes
    ll best = LLONG_MAX;
    
    for (int k = 1; k < 50; k++) {
        ll base = 1;
        for (int i = 0; i < k; i++) {
            if ((i128)base * primes[i] > (i128)1e15) { base = -1; break; }
            base *= primes[i];
        }
        if (base == -1) break;
        
        // Now multiply base by small primes to get φ(d)/(d-1) < target
        ll d = base;
        while (d < best) {
            long double r = phi_ratio(d);
            long double resilience = r * d / (d - 1);
            if (resilience < target) {
                best = min(best, d);
                break;
            }
            // Multiply by smallest prime factor (usually 2)
            if ((i128)d * 2 > (i128)1e15) break;
            d *= 2;
        }
        
        // Also try multiplying by 3, 5, etc. for better granularity
        for (int mult : {3, 4, 5, 6}) {
            d = base * mult;
            if (d <= 0 || d >= best) continue;
            long double r = phi_ratio(d);
            long double resilience = r * d / (d - 1);
            if (resilience < target) {
                best = min(best, d);
            }
        }
    }
    
    cout << best << "\n";
    return 0;
}
