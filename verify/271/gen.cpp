#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    
    string mode = "small";
    if (argc > 1) mode = argv[1];
    
    long long N;
    if (mode == "small") {
        N = rand_ll(2, 10000);
    } else {
        // For large: use a product of several small primes (but not the full PE number)
        vector<long long> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        N = 1;
        int cnt = rand() % 6 + 2; // 2-7 primes
        for (int i = 0; i < cnt; i++) {
            N *= primes[rand() % primes.size()];
            if (N > 100000000000000LL) { N /= primes[rand() % primes.size()]; break; }
        }
        if (N < 2) N = 91;
    }
    
    assert(N >= 2);
    cout << N << "\n";
    return 0;
}
