#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    struct Test { ll U, K; };
    vector<Test> tests(10);

    // 1: PE original (U=1e6, K=1234567890) -> answer: 2781579195314827256
    tests[0] = {1000000, 1234567890};

    // 2-3: smallest
    tests[1] = {10, 1};
    tests[2] = {12, 1};

    // 4-5: small
    tests[3] = {20, 2};
    tests[4] = {50, 3};

    // 6: S(1000) = 614538266565663 (known)
    tests[5] = {1000, 1234567890};

    // 7-8: medium
    tests[6] = {100, 10};
    tests[7] = {200, 100};

    // 9-10: larger
    tests[8] = {500, 1000};
    tests[9] = {1000, 10000};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << tests[i].U << " " << tests[i].K << "\n";
        fout.close();
        cout << "Generated " << filename << " with U=" << tests[i].U << " K=" << tests[i].K << "\n";
    }

    return 0;
}
