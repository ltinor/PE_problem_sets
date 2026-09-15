#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand() % (r - l + 1));
}

// Generate a small random test case for the reduced PE 950:
//   N  C  m   (m is not a perfect square so p = 1/sqrt(m) is irrational)

int main(int argc, char* argv[]) {
    srand((unsigned)time(0) ^ (unsigned)getpid());

    string mode = "small";
    if (argc > 1) mode = argv[1];

    ll N, C, m;

    if (mode == "small") {
        N = rand_ll(1, 60);
        C = rand_ll(1, 30);
        m = rand_ll(2, 300);
    } else if (mode == "medium") {
        N = rand_ll(1, 2000);
        C = rand_ll(1, 200);
        m = rand_ll(2, 5000);
    } else { // large
        N = rand_ll(1, 100000);
        C = rand_ll(1, 1000);
        m = rand_ll(2, 1000000);
    }

    // avoid perfect squares (keeps p irrational)
    ll r = (ll)sqrtl((long double)m);
    while (r * r == m) {
        m = rand_ll(2, (mode == "small" ? 300 : (mode == "medium" ? 5000 : 1000000)));
        r = (ll)sqrtl((long double)m);
    }

    cout << N << " " << C << " " << m << "\n";
    return 0;
}
