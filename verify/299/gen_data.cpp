#include <bits/stdc++.h>
using namespace std;
#define ll long long

// Reduced-data generator for the "simple version" of PE 299.
// Original PE asks N = 10^8 (answer 549936643); here N is reduced to <= 100000.
// Checkpoints: N=100 -> 92, N=100000 -> 320471.
int main() {
    system("mkdir -p data");

    vector<ll> test_cases = {10, 20, 50, 100, 150, 200, 500, 1000, 10000, 100000};

    for (size_t i = 0; i < test_cases.size(); i++) {
        char filename[64];
        snprintf(filename, sizeof(filename), "data/%02zu.in", i + 1);
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
