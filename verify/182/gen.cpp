#include<bits/stdc++.h>
using namespace std;
#define ll long long

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

// Generate small random primes for testing
bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    if (mode == "small") {
        // Use small primes for quick brute verification
        int primes[] = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
        int np = 14;
        int p = primes[rand_int(0, np-1)];
        int q = primes[rand_int(0, np-1)];
        while (q == p) q = primes[rand_int(0, np-1)];
        cout << p << " " << q << "\n";
    } else {
        cout << "1009 3643\n";
    }

    return 0;
}
