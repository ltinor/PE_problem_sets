#include <iostream>
#include <cstdint>
using namespace std;

int64_t multiplicative_order_of_2(int64_t m) {
    if (m <= 1) return 0;
    int64_t phi = m, temp = m;
    for (int64_t p = 2; p * p <= temp; p++) {
        if (temp % p == 0) {
            phi = phi / p * (p - 1);
            while (temp % p == 0) temp /= p;
        }
    }
    if (temp > 1) phi = phi / temp * (temp - 1);
    
    int64_t order = phi;
    for (int64_t p = 2; p * p <= phi; p++) {
        if (phi % p == 0) {
            while (order % p == 0) {
                int64_t candidate = order / p;
                int64_t result = 1, base = 2 % m, exp = candidate;
                while (exp > 0) {
                    if (exp & 1) result = (result * base) % m;
                    base = (base * base) % m;
                    exp >>= 1;
                }
                if (result == 1) order = candidate;
                else break;
            }
        }
    }
    return order;
}

int64_t S_out(int64_t N) {
    int64_t total = 0;
    for (int64_t n = 2; n <= N; n += 2)
        total += multiplicative_order_of_2(n - 1);
    return total;
}

int64_t S_in(int64_t N) {
    int64_t total = 0;
    for (int64_t n = 2; n <= N; n += 2)
        total += multiplicative_order_of_2(n + 1);
    return total;
}

int main() {
    int64_t target = 621073558;
    
    // Try out-shuffles
    for (int64_t N = 100000; N <= 130000; N += 2000) {
        int64_t s = S_out(N);
        cout << "Out S(" << N << ") = " << s << endl;
        if (s >= target) break;
    }
    
    // Try in-shuffles  
    for (int64_t N = 100000; N <= 200000; N += 5000) {
        int64_t s = S_in(N);
        cout << "In S(" << N << ") = " << s << endl;
        if (s >= target) break;
    }
    
    // Fine search near S(108000)
    cout << "\nFine search:" << endl;
    int64_t lo = 104000, hi = 110000;
    while (lo < hi) {
        int64_t mid = (lo + hi) / 2;
        if (mid % 2 == 1) mid++;
        int64_t s = S_out(mid);
        cout << "S(" << mid << ") = " << s << endl;
        if (s < target) lo = mid + 2;
        else hi = mid;
    }
    cout << "Final: S(" << lo << ") = " << S_out(lo) << endl;
    
    return 0;
}
