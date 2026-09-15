#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    // 10 test cases
    vector<tuple<ll, ll, ll>> test_cases(10);

    // 1: sample (PE original: 28433, 7830457, 1)
    test_cases[0] = {28433, 7830457, 1};

    // 2-3: small
    test_cases[1] = {3, 10, 0};        // 3*2^10 = 3072
    test_cases[2] = {7, 5, 3};         // 7*32+3 = 227

    // 4-6: random large
    for (int i = 3; i < 6; i++) {
        ll A = rand_ll(1, 100000);
        ll B = rand_ll(1, 10000000);
        ll C = rand_ll(0, 100000);
        test_cases[i] = {A, B, C};
    }

    // 7-8: boundary
    test_cases[6] = {1, 1, 0};          // min B
    test_cases[7] = {100000, 10000000, 100000}; // max

    // 9-10: more random
    for (int i = 8; i < 10; i++) {
        ll A = rand_ll(1, 50000);
        ll B = rand_ll(5000000, 10000000);
        ll C = rand_ll(0, 50000);
        test_cases[i] = {A, B, C};
    }

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << get<0>(test_cases[i]) << " "
             << get<1>(test_cases[i]) << " "
             << get<2>(test_cases[i]) << "\n";
        fout.close();
        cout << "Generated " << filename << " with A=" << get<0>(test_cases[i])
             << " B=" << get<1>(test_cases[i]) << " C=" << get<2>(test_cases[i]) << "\n";
    }

    return 0;
}
