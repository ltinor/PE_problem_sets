// PE 326 - Generate all test data
#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * (ll)rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));
    
    struct TestCase { ll N, M; string desc; };
    vector<TestCase> tc(10);
    
    // 1: sample from problem
    tc[0] = {10, 10, "sample"};
    // 2: PE verification f(10^4, 10^3) = 97158
    tc[1] = {10000, 1000, "PE partial"};
    // 3-5: small random
    for (int i = 2; i < 5; i++)
        tc[i] = {rand_ll(1, 1000), rand_ll(1, 100), "small"};
    // 6-7: medium
    tc[5] = {rand_ll(50000, 200000), rand_ll(50, 5000), "medium"};
    tc[6] = {rand_ll(100000, 500000), rand_ll(100, 10000), "medium"};
    // 8: larger
    tc[7] = {rand_ll(1000000, 2000000), rand_ll(1000, 50000), "large"};
    // 9-10: boundary
    tc[8] = {1, 1, "min"};
    tc[9] = {5000000, 100000, "max_adapted"};
    
    for (int i = 0; i < 10; i++) {
        char fn[32];
        snprintf(fn, sizeof(fn), "data/%02d.in", i + 1);
        ofstream f(fn);
        f << tc[i].N << " " << tc[i].M << "\n";
        f.close();
        printf("Generated %s: N=%lld M=%lld (%s)\n", fn, tc[i].N, tc[i].M, tc[i].desc.c_str());
    }
    
    // Also create the PE verification file
    {
        ofstream f("data/pe_verify.in");
        f << "1000000000000 1000000\n";  // PE: f(10^12, 10^6)
        f.close();
        printf("Generated data/pe_verify.in: PE f(10^12,10^6)\n");
    }
    
    return 0;
}
