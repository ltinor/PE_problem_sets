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

int main() {
    for (int64_t N : {10000, 20000, 50000, 100000, 200000}) {
        int64_t total = 0;
        for (int64_t n = 2; n <= N; n += 2) {
            total += multiplicative_order_of_2(n - 1);
        }
        cout << "S(" << N << ") = " << total << endl;
    }
    return 0;
}
