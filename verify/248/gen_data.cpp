#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<pair<ll, ll>> test_cases(10);

    // 1: PE original
    // phi(n) = 13! = 6227020800
    // Wait, the problem says phi(n) = 13! which is 6227020800
    test_cases[0] = {6227020800LL, 150000LL};

    // 2-3: very small K
    test_cases[1] = {1, 1};        // phi(n)=1 → n=1,2
    test_cases[2] = {2, 2};        // phi(n)=2 → n=3,4,6

    // 4-5: small K
    test_cases[3] = {4, 3};        // phi(n)=4 → n=5,8,10,12
    test_cases[4] = {6, 2};        // phi(n)=6 → n=7,9,14,18

    // 6-7: medium-small K
    test_cases[5] = {8, 1};        // phi(n)=8
    test_cases[6] = {12, 3};       // phi(n)=12

    // 8: edge case
    test_cases[7] = {10, 2};       // phi(n)=10 → n=11,22

    // 9-10: medium K
    test_cases[8] = {24, 5};       // phi(n)=24
    test_cases[9] = {72, 10};      // phi(n)=72

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with K=" << test_cases[i].first << " T=" << test_cases[i].second << "\n";
    }

    return 0;
}
